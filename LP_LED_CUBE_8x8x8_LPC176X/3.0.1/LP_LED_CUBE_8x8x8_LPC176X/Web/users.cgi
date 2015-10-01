t <html>
t <head>
t <title>Users Settings</title>
t <link rel="stylesheet" type="text/css" href="style.css">
t <script language="JavaScript" type="text/javascript" src="javascript.js"></script>
t </head>
t <body>
c E A
t <table class='table_data'>
t <tr align='center'><td class='table_data_header'>Delete all users</td></tr>
t <tr align='center'>
t <form method="POST">
t <td class='table_data_row'>
t <input type="hidden" value="yes" name="delete_users">
t <input type="button" value="Delete all"
t OnClick="confirmForm(this.form, 'Are you sure you want to delete all users?')">
t </td></form></tr>
t </table><br>
t <table class="table_data" style="cursor: pointer;">
t <tr align="left"><td class="table_data_header">Add User</td></tr>
t </table>
t <table class="table_data" id="table_add_user" style="cursor: pointer;"><tr align="left">
t <form method='post'><td class="table_data_row" width="40%">Username *</td>
t <td class="table_data_row"><input type="text" name="username" 
c E B 0 maxlength="%d"/>
t </td></tr><tr align='left'>
t <td class="table_data_row">Password *</td><td class="table_data_row">
t <input type="text" name="password" 
c E B 1 maxlength="%d"/>
t </td></tr><tr align='left'>
t <td class="table_data_row">First name *</td><td class="table_data_row">
t <input type="text" name="first_name" 
c E B 2 maxlength="%d"/>
t </td></tr><tr align='left'>
t <td class="table_data_row">Last name *</td><td class="table_data_row">
t <input type="text" name="last_name" 
c E B 3 maxlength="%d"/>
t </td></tr><tr align='left'>
t <td class="table_data_row">E-mail *</td><td class="table_data_row">
t <input type="text" name="email" 
c E B 4 maxlength="%d"/>
t </td></tr><tr>
t <td class="table_data_footer" colspan="2" align="center">
t <input type="hidden" name="add_user" value="yes"/>
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