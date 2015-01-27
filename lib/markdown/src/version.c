#include "version.h"

void
markdown_version(int *major, int *minor, int *revision)
{
	*major = MARKDOWN_VERSION_MAJOR;
	*minor = MARKDOWN_VERSION_MINOR;
	*revision = MARKDOWN_VERSION_REVISION;
}
