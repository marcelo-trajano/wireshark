/*
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 2001 Gerald Combs
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "config.h"
#include "ftypes-int.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <epan/to_str.h>
#include <wsutil/time_util.h>


static int
cmp_order(const fvalue_t *a, const fvalue_t *b)
{
	return nstime_cmp(&(a->value.time), &(b->value.time));
}

/*
 * Get a nanoseconds value, starting at "p".
 *
 * Returns true on success, false on failure.
 */
static gboolean
get_nsecs(const char *startp, int *nsecs)
{
	int ndigits;
	int scale;
	const char *p;
	int val;
	int digit;
	int i;

	/*
	 * How many characters are in the string?
	 */
	ndigits = (int)strlen(startp);

	/*
	 * If there are N characters in the string, the last of the
	 * characters would be the digit corresponding to 10^(9-N)
	 * nanoseconds.
	 */
	scale = 9 - ndigits;

	/*
	 * Start at the last character, and work backwards.
	 */
	p = startp + ndigits;
	val = 0;
	while (p != startp) {
		p--;

		if (!g_ascii_isdigit(*p)) {
			/*
			 * Not a digit - error.
			 */
			return FALSE;
		}
		digit = *p - '0';
		if (digit != 0) {
			/*
			 * Non-zero digit corresponding to that number
			 * of (10^scale) units.
			 *
			 * If scale is less than zero, this digit corresponds
			 * to a value less than a nanosecond, so this number
			 * isn't valid.
			 */
			if (scale < 0)
				return FALSE;
			for (i = 0; i < scale; i++)
				digit *= 10;
			val += digit;
		}
		scale++;
	}
	*nsecs = val;
	return TRUE;
}

static gboolean
relative_val_from_unparsed(fvalue_t *fv, const char *s, gboolean allow_partial_value _U_, gchar **err_msg)
{
	const char    *curptr;
	char *endptr;
	gboolean negative = FALSE;

	curptr = s;

	if (*curptr == '-') {
		negative = TRUE;
		curptr++;
	}

	/*
	 * If it doesn't begin with ".", it should contain a seconds
	 * value.
	 */
	if (*curptr != '.') {
		/*
		 * Get the seconds value.
		 */
		fv->value.time.secs = strtoul(curptr, &endptr, 10);
		if (endptr == curptr || (*endptr != '\0' && *endptr != '.'))
			goto fail;
		curptr = endptr;
		if (*curptr == '.')
			curptr++;	/* skip the decimal point */
	} else {
		/*
		 * No seconds value - it's 0.
		 */
		fv->value.time.secs = 0;
		curptr++;		/* skip the decimal point */
	}

	/*
	 * If there's more stuff left in the string, it should be the
	 * nanoseconds value.
	 */
	if (*curptr != '\0') {
		/*
		 * Get the nanoseconds value.
		 */
		if (!get_nsecs(curptr, &fv->value.time.nsecs))
			goto fail;
	} else {
		/*
		 * No nanoseconds value - it's 0.
		 */
		fv->value.time.nsecs = 0;
	}

	if (negative) {
		fv->value.time.secs = -fv->value.time.secs;
		fv->value.time.nsecs = -fv->value.time.nsecs;
	}
	return TRUE;

fail:
	if (err_msg != NULL)
		*err_msg = ws_strdup_printf("\"%s\" is not a valid time.", s);
	return FALSE;
}


/* Returns TRUE if 's' starts with an abbreviated month name. */
static gboolean
parse_month_name(const char *s, int *tm_mon)
{
	const char *months[] = {
		"Jan", "Feb", "Mar", "Apr", "May", "Jun",
		"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
	};
	for (int i = 0; i < 12; i++) {
		if (g_ascii_strncasecmp(s, months[i], 3) == 0) {
			*tm_mon = i;
			return TRUE;
		}
	}
	return FALSE;
}

/* Parses an absolute time value from a string. The string cannot have
 * a time zone suffix and is always interpreted in local time.
 *
 * OS-dependent; e.g., on 32 bit versions of Windows when compiled to use
 * _mktime32 treats dates before January 1, 1970 as invalid.
 * (https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/mktime-mktime32-mktime64)
 */
static gboolean
absolute_val_from_string(fvalue_t *fv, const char *s, gchar **err_msg)
{
	struct tm tm;
	char    *curptr = NULL;
	gboolean has_seconds = TRUE;

	memset(&tm, 0, sizeof(tm));

	if (strlen(s) < sizeof("2000-1-1") - 1)
		goto fail;

	/* Do not use '%b' to parse the month name, it is locale-specific. */
	if (s[3] == ' ' && parse_month_name(s, &tm.tm_mon))
		curptr = ws_strptime(s + 4, "%d, %Y %H:%M:%S", &tm);

	if (curptr == NULL)
		curptr = ws_strptime(s,"%Y-%m-%dT%H:%M:%S", &tm);
	if (curptr == NULL)
		curptr = ws_strptime(s,"%Y-%m-%d %H:%M:%S", &tm);
	if (curptr == NULL) {
		has_seconds = FALSE;
		curptr = ws_strptime(s,"%Y-%m-%d %H:%M", &tm);
	}
	if (curptr == NULL)
		curptr = ws_strptime(s,"%Y-%m-%d %H", &tm);
	if (curptr == NULL)
		curptr = ws_strptime(s,"%Y-%m-%d", &tm);
	if (curptr == NULL)
		goto fail;
	tm.tm_isdst = -1;	/* let the computer figure out if it's DST */
	fv->value.time.secs = mktime(&tm);
	if (*curptr != '\0') {
		/*
		 * Something came after the seconds field; it must be
		 * a nanoseconds field.
		 */
		if (*curptr != '.' || !has_seconds)
			goto fail;	/* it's not */
		curptr++;	/* skip the "." */
		if (!g_ascii_isdigit((unsigned char)*curptr))
			goto fail;	/* not a digit, so not valid */
		if (!get_nsecs(curptr, &fv->value.time.nsecs))
			goto fail;
	} else {
		/*
		 * No nanoseconds value - it's 0.
		 */
		fv->value.time.nsecs = 0;
	}

	if (fv->value.time.secs == -1) {
		/*
		 * XXX - should we supply an error message that mentions
		 * that the time specified might be syntactically valid
		 * but might not actually have occurred, e.g. a time in
		 * the non-existent time range after the clocks are
		 * set forward during daylight savings time (or possibly
		 * that it's in the time range after the clocks are set
		 * backward, so that there are two different times that
		 * it could be)?
		 */
		goto fail;
	}

	return TRUE;

fail:
	if (err_msg != NULL)
		*err_msg = ws_strdup_printf("\"%s\" is not a valid absolute time. Example: \"Nov 12, 1999 08:55:44.123\" or \"2011-07-04 12:34:56\"",
		    s);
	return FALSE;
}

static gboolean
absolute_val_from_unparsed(fvalue_t *fv, const char *s, gboolean allow_partial_value _U_, gchar **err_msg)
{
	return absolute_val_from_string(fv, s, err_msg);
}

static void
time_fvalue_new(fvalue_t *fv)
{
	fv->value.time.secs = 0;
	fv->value.time.nsecs = 0;
}

static void
time_fvalue_set(fvalue_t *fv, const nstime_t *value)
{
	fv->value.time = *value;
}

static gpointer
value_get(fvalue_t *fv)
{
	return &(fv->value.time);
}

static char *
absolute_val_to_repr(wmem_allocator_t *scope, const fvalue_t *fv, ftrepr_t rtype, int field_display)
{
	gchar *rep;
	char *buf;

	switch (rtype) {
		case FTREPR_DISPLAY:
			rep = abs_time_to_str(scope, &fv->value.time,
					field_display, TRUE);
			break;

		case FTREPR_DFILTER:
			/* absolute_val_from_string only accepts local time,
			 * with no time zone, so match that. */
			rep = abs_time_to_str(scope, &fv->value.time,
					ABSOLUTE_TIME_LOCAL, FALSE);
			break;

		default:
			ws_assert_not_reached();
			break;
	}

	if (rtype == FTREPR_DFILTER) {
		buf = wmem_strdup_printf(scope, "\"%s\"", rep);
		wmem_free(scope, rep);
	}
	else {
		buf = rep;
	}
	return buf;
}

static char *
relative_val_to_repr(wmem_allocator_t *scope, const fvalue_t *fv, ftrepr_t rtype _U_, int field_display _U_)
{
	return rel_time_to_secs_str(scope, &fv->value.time);
}

void
ftype_register_time(void)
{

	static ftype_t abstime_type = {
		FT_ABSOLUTE_TIME,		/* ftype */
		"FT_ABSOLUTE_TIME",		/* name */
		"Date and time",		/* pretty_name */
		0,				/* wire_size */
		time_fvalue_new,		/* new_value */
		NULL,				/* free_value */
		absolute_val_from_unparsed,	/* val_from_unparsed */
		absolute_val_from_string,	/* val_from_string */
		NULL,				/* val_from_charconst */
		absolute_val_to_repr,		/* val_to_string_repr */

		{ .set_value_time = time_fvalue_set },	/* union set_value */
		{ .get_value_ptr = value_get },		/* union get_value */

		cmp_order,
		NULL,				/* cmp_bitwise_and */
		NULL,				/* cmp_contains */
		NULL,				/* cmp_matches */

		NULL,
		NULL
	};
	static ftype_t reltime_type = {
		FT_RELATIVE_TIME,		/* ftype */
		"FT_RELATIVE_TIME",		/* name */
		"Time offset",			/* pretty_name */
		0,				/* wire_size */
		time_fvalue_new,		/* new_value */
		NULL,				/* free_value */
		relative_val_from_unparsed,	/* val_from_unparsed */
		NULL,				/* val_from_string */
		NULL,				/* val_from_charconst */
		relative_val_to_repr,		/* val_to_string_repr */

		{ .set_value_time = time_fvalue_set },	/* union set_value */
		{ .get_value_ptr = value_get },		/* union get_value */

		cmp_order,
		NULL,				/* cmp_bitwise_and */
		NULL,				/* cmp_contains */
		NULL,				/* cmp_matches */

		NULL,
		NULL
	};

	ftype_register(FT_ABSOLUTE_TIME, &abstime_type);
	ftype_register(FT_RELATIVE_TIME, &reltime_type);
}

/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 8
 * tab-width: 8
 * indent-tabs-mode: t
 * End:
 *
 * vi: set shiftwidth=8 tabstop=8 noexpandtab:
 * :indentSize=8:tabSize=8:noTabs=false:
 */
