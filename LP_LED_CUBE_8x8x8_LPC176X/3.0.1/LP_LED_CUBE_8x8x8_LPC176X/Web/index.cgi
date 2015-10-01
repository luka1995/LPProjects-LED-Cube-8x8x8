t <html>
t <head>
t <title>Animations</title>
t <link rel="stylesheet" type="text/css" href="style.css">
t </head>
t <body>
t <table class="table_data">
t <tr>
t <td width="10%" class="table_data_header">Nr.</td>
t <td class="table_data_header">Animation name</td>
t <td width="10%" class="table_data_header">File size</td>
t <td width="10%" class="table_data_header">Count</td>
t <td width="10%" class="table_data_header">Delete</td>
t <td width="10%" class="table_data_header">Play</td>
t </tr>
c B A
t </table>
t <br>
t <table class="table_data">
t <tr><td class="table_data_header">Delete All</td></tr>
t <form method="POST">
t <tr><td align="center" class="table_data_row">
t <input type="hidden" value="yes" name="delete_all_ani">
t <input type="button" value="Delete" OnClick="this.form.submit()">
t </th></tr>
t </form>
t </tr>
t </table>
t <br>
t <table class="table_data">
t <tr><td class="table_data_header">Upload Animation File</td></tr>
t <form method="POST" enctype="multipart/form-data">
t <tr><td align="center" class="table_data_row">
t <input name="File" type="file" accept=".ani" size="50" maxlength="1000">
t <input type="button" value="Send" OnClick="this.form.submit()">
t </td></tr>
t </form>
t </tr>
t </table>
t <br>
t <center>
c Z
t Copyright &#169; LPProjects
t </center>
t </body>
t </html>
. End of script must be closed with period.
