/************************************** IS_UPPER ***************************************/
/* This tiny macro checks whether a character is uppercase */
/* It uses NO CONDITIONAL STATEMENTS, hence it is useful in systems where read ahead is crucial */
/* The usage is limited for systems supporting the old ASCII 32 non extended standart, and older versions of unicode */
/* Can be modified to suit different standarts. */
/***************************************************************************************/

#define IS_UPPER(input) !!(((input - 1) % 90UL) >> 6)

