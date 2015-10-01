/*----------------------------------------------------------------------------
 *      RL-ARM - TCPnet
 *----------------------------------------------------------------------------
 *      Name:    HTTP_ERR.C
 *      Purpose: HTTP Server Error Page Definitions
 *      Rev.:    V4.54
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2012 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <RTL.h>

/* Note: Keep HTTP Error pages small sized. */

/* HTTP Error 401 - Unauthorized access. */
const U8 http_err_401[] = {
        "<h2>Error 401 - Unauthorized Access</h2>"
        "You are not authorized to access this server."};

/* HTTP Error 403 - Forbidden */
const U8 http_err_403[] = {
        "<h2>Error 403 - Forbidden</h2>"
        "You don't have permission to access this resource."};

/* HTTP Error 404 - Not Found */
const U8 http_err_404[] = {
				"<h2>Error 404 - Not Found</h2>"
        "The requested URL was not found on this server."};

/* HTTP Error 501 - Not Implemented */
const U8 http_err_501[] = {
        "<h2>Error 501 - Not Implemented</h2>"
        "The requested Method is not supported."};

/* Common HTTP Error Page Header */
const U8 http_err_head[] = {
        "<head><title>Server Error</title></head>"
        "<body>"};

/* Common HTTP Error Page Footer */
const U8 http_err_foot[] = {
        "<hr>"
        "<i>LPProjects<br>"
				"<i>Copyright 2014<br>"
        "<a href=http://www.lpprojects.com>www.lpprojects.com</a></i>"
        "</body>"};

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
