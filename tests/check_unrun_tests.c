/*
 * Check: a unit test framework for C
 * Copyright (C) 2001, 2002 Arien Malec
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include "../lib/libcompat.h"

#include <stdlib.h>
#include <stdio.h>
#include <check.h>

#include <string.h>

#include "check_list.h"

START_TEST(test_create)
{
  List *lp = NULL;

  ck_assert_msg (check_list_val(lp) == NULL,
	       "Current list value should be NULL for NULL list");

  lp = check_list_create();

  ck_assert_msg (check_list_val(lp) == NULL,
	       "Current list value should be NULL for newly created list");

  ck_assert_msg (check_list_at_end(lp),
	       "Newly created list should be at end");
  check_list_advance(lp);
  ck_assert_msg (check_list_at_end(lp),
	       "Advancing a list at end should produce a list at end");
  check_list_free (lp);
}
END_TEST

START_TEST(test_free)
{
  List *lp = check_list_create();
  char data_abc[] = "abc";
  char data_123[] = "123";

  check_list_add_end (lp, data_abc);
  check_list_add_end (lp, data_123);
  check_list_add_end (lp, NULL);
  check_list_free (lp);
}
END_TEST

START_TEST(test_add_end)
{
  List * lp = check_list_create();
  char tval[] = "abc";
  
  check_list_add_end (lp, tval);
  
  ck_assert_msg (check_list_val (lp) != NULL,
	       "List current val should not be null after new insertion");
  ck_assert_msg (!check_list_at_end (lp),
	       "List should be at end after new insertion");
  ck_assert_msg (strcmp(tval, (char *) check_list_val (lp)) == 0,
	       "List current val should equal newly inserted val");
  check_list_free (lp);
}
END_TEST

START_TEST(test_add_front)
{
  List * lp = check_list_create();
  char tval[] = "abc";
  
  check_list_add_front (lp, tval);
  
  ck_assert_msg (check_list_val (lp) != NULL,
	       "List current val should not be null after new insertion");
  ck_assert_msg (strcmp(tval, (char *) check_list_val (lp)) == 0,
	       "List current val should equal newly inserted val");
  check_list_free (lp);
}
END_TEST

START_TEST(test_add_end_and_next)
{
  List *lp = check_list_create();
  char tval1[] = "abc";
  char tval2[] = "123";
  
  check_list_add_end (lp, tval1);
  check_list_add_end (lp, tval2);
  check_list_front(lp);
  ck_assert_msg (strcmp (tval1, (char *)check_list_val (lp)) == 0,
	       "List head val should equal first inserted val");
  check_list_advance (lp);
  ck_assert_msg (!check_list_at_end (lp),
	       "List should not be at end after two adds and one next");
  ck_assert_msg (strcmp (tval2, (char *)check_list_val (lp)) == 0,
	       "List val should equal second inserted val");
  check_list_advance(lp);
  ck_assert_msg (check_list_at_end (lp),
	       "List should be at and after two adds and two nexts");
  check_list_free (lp);
}
END_TEST


START_TEST(test_add_front_and_next)
{
  List * lp = check_list_create();
  char tval1[] = "abc";
  char tval2[] = "123";
  
  check_list_add_front (lp, tval1);
  check_list_add_front (lp, tval2);
  check_list_front(lp);
  ck_assert_msg (strcmp (tval2, (char *)check_list_val (lp)) == 0,
	       "List head val should equal last inserted val");
  check_list_advance (lp);
  ck_assert_msg (!check_list_at_end (lp),
	       "List should not be at end after two adds and one next");
  ck_assert_msg (strcmp (tval1, (char *)check_list_val (lp)) == 0,
	       "List val should equal first inserted val");
  check_list_advance(lp);
  ck_assert_msg (check_list_at_end (lp),
	       "List should be at and after two adds and two nexts");
  check_list_free (lp);
}
END_TEST

START_TEST(test_add_a_bunch)
{
  List *lp;
  int i, j;
  char tval1[] = "abc";
  char tval2[] = "123";
  for (i = 0; i < 3; i++) {
    lp = check_list_create();
    for (j = 0; j < 1000; j++) {
      check_list_add_end (lp, tval1);
      check_list_add_front (lp, tval2);
    }
    check_list_free(lp);
  }
}
END_TEST

static Suite *make_empty_suit (void)
{
  Suite *s = suite_create("Empty");
  TCase * tc = tcase_create("CoreEmpty");

  suite_add_tcase (s, tc);
  return s;
}

/* Commented out to test how Check reacts when there
* is defined tests which are not included in any suite.
*/
static Suite *make_list_suite_one (void)
{
  Suite *s = suite_create("ListsOne");
  TCase * tc = tcase_create("CoreOne");

  suite_add_tcase (s, tc);
  tcase_add_test (tc, test_create);
  tcase_add_test (tc, test_free);
  /* tcase_add_test (tc, test_add_end); */
  /* tcase_add_test (tc, test_add_front); */

  return s;
}

static Suite *make_list_suite_two (void)
{
  Suite *s = suite_create("ListsTwo");
  TCase * tc = tcase_create("CoreTwo");

  suite_add_tcase (s, tc);
  tcase_add_test (tc, test_add_end_and_next);
  /* tcase_add_test (tc, test_add_front_and_next); */
  /* case_add_test (tc, test_add_a_bunch); */

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = make_empty_suit();
  sr = srunner_create(s);
  srunner_add_suite(sr, make_list_suite_one());
  srunner_add_suite(sr, make_list_suite_two());

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
/* int main (void) */
/* { */
/*   int number_failed; */
/*   SRunner *sr = (SRunner *)emalloc(sizeof(SRunner));     #<{(| freed in srunner_free |)}># */
/*  */
/*   #<{(| fork_setup(); |)}># */
/*   #<{(| setup_fixture(); |)}># */
/*   #<{(| setup(); |)}># */
/*  */
/*   sr = srunner_create (make_master_suite()); */
/*   srunner_add_suite(sr, make_list_suite_one()); */
/*   srunner_add_suite(sr, make_list_suite_two()); */
/*    */
/*   #<{(| printf ("Ran %d tests in subordinate suite\n", sub_ntests); |)}># */
/*   srunner_run_all (sr, CK_VERBOSE); */
/*   number_failed = srunner_ntests_failed(sr); */
/*   srunner_free(sr); */
/*   return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE; */
/* } */

