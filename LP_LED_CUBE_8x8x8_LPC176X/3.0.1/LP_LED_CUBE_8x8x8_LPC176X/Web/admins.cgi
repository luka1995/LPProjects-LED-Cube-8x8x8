t <html>
t <head>
t <title>Admins Settings</title>
t <link rel="stylesheet" type="text/css" href="style.css">
t <script language="JavaScript" type="text/javascript" src="javascript.js"></script>
t </head>
t <body>
c D A
t <table class="table_data" style="cursor: pointer;">
t <tr align="left"><td class="table_data_header">Add Admin</td></tr>
t </table>
t <table class="table_data" id="table_add_admin" style="cursor: pointer;"><tr align="left">
t <form method='post'><td class="table_data_row" width="40%">Username *</td>
t <td class="table_data_row"><input type="text" name="username" 
c D B 0 maxlength="%d"/>
t </td></tr><tr align='left'>
t <td class="table_data_row">Password *</td><td class="table_data_row">
t <input type="text" name="password" 
c D B 1 maxlength="%d"/>
t </td></tr><tr align="left">
t <td class="table_data_row">E-mail *</td><td class="table_data_row">
t <input type="text" name="email" 
c D B 2 maxlength="%d"/>
t </td></tr><tr>
t <td class="table_data_footer" colspan="2" align="center">
t <input type="hidden" name="add_admin" value="yes"/>
t <input type="submit" value="Add"/>
t </td></form></tr>
t </table>
t <br>
t <center>
c Z
t Copyright &#169; LPProjects
t </center>
t </body>
t </html>
. End of script must be closed with period.