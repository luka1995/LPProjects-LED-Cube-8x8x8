t <html>
t <head>
t <title>Network Settings</title>
t <link rel="stylesheet" type="text/css" href="style.css">
t </head>
t <body>
t <table class="table_data">
# Header
t <table class="table_data">
t <tr align="left"><td class="table_data_header" colspan="2">
t Ethernet Network Interface Settings
t </tr>
t <form method="get">
# IP Address
t <tr align="left"><td class="table_data_row" width="40%%">
t IP Address
t </td><td class="table_data_row">
t <input type="text" name="ip"
c F 0 value="%d.%d.%d.%d"/>
t </td></tr>
# Subnet Mask
t <tr align="left"><td class="table_data_row" width="40%%">
t Subnet Mask
t </td><td class="table_data_row">
t <input type="text" name="msk"
c F 1 value="%d.%d.%d.%d"/>
t </td></tr>
# Default Gateway
t <tr align="left"><td class="table_data_row" width="40%%">
t Default Gateway
t </td><td class="table_data_row">
t <input type="text" name="gw"
c F 2 value="%d.%d.%d.%d"/>
t </td></tr>
# Primary DNS Server
t <tr align="left"><td class="table_data_row" width="40%%">
t Primary DNS Server
t </td><td class="table_data_row">
t <input type="text" name="pdns"
c F 3 value="%d.%d.%d.%d"/>
t </td></tr>
# Secondary DNS Server
t <tr align="left"><td class="table_data_row" width="40%%">
t Secondary DNS Server
t </td><td class="table_data_row">
t <input type="text" name="sdns"
c F 4 value="%d.%d.%d.%d"/>
t </td></tr>
# Apply
t <tr align="center"><td class="table_data_footer" colspan="2">
t <input id="network_save" type="submit"
t value="Apply"/>
t </td></tr></form>
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
