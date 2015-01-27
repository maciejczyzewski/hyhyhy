/* version.h - holds Markdown's version */

#ifndef MARKDOWN_VERSION_H
#define MARKDOWN_VERSION_H

#ifdef __cplusplus
extern "C" {
#endif


/*************
 * CONSTANTS *
 *************/

#define MARKDOWN_VERSION "3.0.1"
#define MARKDOWN_VERSION_MAJOR 3
#define MARKDOWN_VERSION_MINOR 0
#define MARKDOWN_VERSION_REVISION 1


/*************
 * FUNCTIONS *
 *************/

/* markdown_version: retrieve Markdown's version numbers */
void markdown_version(int *major, int *minor, int *revision);


#ifdef __cplusplus
}
#endif

#endif /** MARKDOWN_VERSION_H **/
