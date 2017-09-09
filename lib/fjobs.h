/* fjobs.h - recording information about the file jobs
   Copyright 1995-2017 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA
   02110-1301, USA.  */

#ifndef FJOBS_H_
# define FJOBS_H_

struct a2ps_job;

/*
 * Relative to the current file
 */
struct file_job
{
  unsigned char * name;			/* Guess what it is :)			*/

  /* A tmp file associated with this file.  It is used only privately
     by a2ps-prog.  If the file is delegated, the output of the
     delegation is stored there. */
  char *delegation_tmpname;

  /* The name under which this file is saved if it has to be delegated
     and is actually stdin.  */
  char *stdin_tmpname;

  const char * type;		/* i.e. ssh key, or UNPRINTABLE		*/
  bool is_toc;			/* Is this a toc, or a real file (used
				 * when --pages=toc)			*/
  struct tm mod_tm;		/* Modif. info for the file 		*/
  bool printable;		/* Can this file be printed?		*/
  bool is_stdin;		/* Is this file named or given by stdin?*/
  int first_sheet;		/* num of the first sheet for this file	*/
  int last_sheet;
  int first_page;		/* Id. but pages			*/
  int last_page;
  int pages;			/* These are defined because it eases	*/
  int sheets;			/* delayed integers (cf. output_marker)	*/
  int num;			/* No of the file in the args		*/
  int top_line;			/* The top most line of the current page */
  int top_page;			/* The first page appearing in curr sheet */
  int lines;			/* Current line number			*/
};


/* in the output session JOB, create a new input session NAME */
struct file_job *
_a2ps_file_job_new (unsigned char * name, int num, struct tm * run_tm);

int file_name_cmp (struct file_job * f1, struct file_job * f2);

void file_job_synchronize_sheets (struct a2ps_job * job);
void file_job_synchronize_pages (struct a2ps_job * job);
void file_job_self_print (struct file_job * file, FILE * stream);
void file_job_unlink_tmpfile (struct file_job * file);
void file_job_free (struct file_job * file_job);

#endif /* !defined (_FJOBS_H) */
