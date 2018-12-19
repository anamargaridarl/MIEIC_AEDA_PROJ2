/*
 * Gradetempl.h
 *
 *  Created on: 25/10/2018
 *      Author: joaomartins
 */

#ifndef SRC_GRADETEMPL_H_
#define SRC_GRADETEMPL_H_

#include <iostream>
#include<string>
/**
 * @brief Function explain the grade 1 of the Report
 * @param os - where to write it
 */
void grade_1(std::ostream &os)
{
	os << "\t The student did very poorly in this month. Effort and progress far from meeting the goals set." << std::endl
	<< "\t Next month requires change of training habits and behavior from the student." << std::endl
	<< std::endl << "\t The grade set to this month was (scale of 1-5): 1 " << std::endl << std::endl;
}



/**
 * @brief Function explain the grade 2 of the Report
 * @param os - where to write it
 */
void grade_2(std::ostream &os)
{
	os << "\t The student's this month's performance is unsatisfactory . Effort and progress weren't enough to meet the goals set." << std::endl
	<< "\t Next month requires improvement on the effort and practice hours of the student." << std::endl
	<< std::endl << "\t The grade set to this month was (scale of 1-5): 2 " << std::endl << std::endl;
}



/**
 * @brief Function explain the grade 3 of the Report
 * @param os - where to write it
 */
void grade_3(std::ostream &os)
{
	os << "The student performance on this month is sufficient. Effort and progress met the goals set." << std::endl
	<< "If the student improves effort and raises practice time better results will be achieved." << std::endl
	<< std::endl << "\t The grade set to this month was (scale of 1-5): 3 " << std::endl << std::endl;
}


/**
 * @brief Function explain the grade 4 of the Report
 * @param os - where to write it
 */

void grade_4(std::ostream &os)
{
	os << "The student evaluation this month is good. The goals set were met very adequately." << std::endl
	<< "If the student pushes himself/herself further, excellence is waiting just around the corner." << std::endl
	<< std::endl << "\t The grade set to this month was (scale of 1-5): 4" << std::endl << std::endl;
}


/**
 * @brief Function explain the grade 5 of the Report
 * @param os - where to write it
 */

void grade_5(std::ostream &os)
{
	os << "The student evaluation for this month is excellent! Effort and progress went beyond the goals set." << std::endl
	<< "Congratulations for this month's performance, same results are to expect on next month's review." << std::endl
	<< std::endl << "\t The grade set to this month was (scale of 1-5): 5 " << std::endl << std::endl;
}


#endif /* SRC_GRADETEMPL_H_ */
