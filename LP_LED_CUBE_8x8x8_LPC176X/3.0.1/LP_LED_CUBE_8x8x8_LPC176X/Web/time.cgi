t <html>
t <head>
t <title>Time Settings</title>
t <link rel="stylesheet" type="text/css" href="style.css">
t <script language="JavaScript" type="text/javascript" src="javascript.js"></script>
t </head>
t <body>
# Time Configuration Header
t <table class="table_data">
t <tr align="left"><td class="table_data_header" colspan="2">
t Current Time / Date
t </tr>
# Current Time
t <tr align="left"><td class="table_data_row" width="40%%">
t Time
t </td><td class="table_data_row">
t <input type="text" id="current_time" readonly 
c C A 0 0 value="%s"/>
t </td></tr>
# Current Date
t <tr align="left"><td class="table_data_row">
t Date
t </td><td class="table_data_row">
t <input type="text" id="current_date" readonly 
c C A 0 1 value="%s"/>
t </td></tr>
t </table>
t <br>
# Format Configuration Header
t <table class="table_data">
t <tr align="left"><td class="table_data_header" colspan="2">
t Configuration
t </td></tr>
t <form method="post">
t <tr align="left"><td class="table_data_row" width="40%%">
t Time Format
t </td><td class="table_data_row">
t <input type="text" maxlength="20" id="time_format" name="time_format"
c C B 0 0 value="%s"/>
t </td></tr><tr align="left"><td class="table_data_row">
t Date Format
t </td><td class="table_data_row">
t <input type="text" maxlength="20" id="date_format" name="date_format"
c C B 0 1 value="%s"/>
t </td></tr><tr align="left"><td class="table_data_row">
t Time Zone Offset
t </td><td class="table_data_row">
t <select name="timezone_offset_select">
t <option value="-12" 
c C B 1 0 0 %s
t >GMT-12:00 International Date Line West</option>
t <option value="-11" 
c C B 1 0 1 %s
t >GMT-11:00 Nome Time</option>
t <option value="-10" 
c C B 1 0 2 %s
t >GMT-10:00 Alaska-Hawaii Standard Time</option>
t <option value="-9" 
c C B 1 0 3 %s
t >GMT-09:00 Yukon Standard Time</option>
t <option value="-8" 
c C B 1 0 4 %s
t >GMT-08:00 Pacific Standard Time</option>
t <option value="-7" 
c C B 1 0 5 %s
t >GMT-07:00 Mountain Standard Time</option>
t <option value="-6" 
c C B 1 0 6 %s
t >GMT-06:00 Central Standard Time</option>
t <option value="-5" 
c C B 1 0 7 %s
t >GMT-05:00 Eastern Standard Time</option>
t <option value="-4" 
c C B 1 0 8 %s
t >GMT-04:00 Atlantic Standard Time</option>
t <option value="-3" 
c C B 1 0 9 %s
t >GMT-03:00</option>
t <option value="-2" 
c C B 1 1 0 %s
t >GMT-02:00 Azores Time</option>
t <option value="-1" 
c C B 1 1 1 %s
t >GMT-01:00 West Africa Time</option>
t <option value="0" 
c C B 1 1 2 %s
t >GMT 00:00 Greenwich Mean Time</option>
t <option value="1" 
c C B 1 1 3 %s
t >GMT+01:00 Central European Time</option>
t <option value="2" 
c C B 1 1 4 %s
t >GMT+02:00 Eastern European Time</option>
t <option value="3" 
c C B 1 1 5 %s
t >GMT+03:00 Baghdad Time</option>
t <option value="4" 
c C B 1 1 6 %s
t >GMT+04:00</option>
t <option value="5" 
c C B 1 1 7 %s
t >GMT+05:00</option>
t <option value="6" 
c C B 1 1 8 %s
t >GMT+06:00</option>
t <option value="7" 
c C B 1 1 9 %s
t >GMT+07:00</option>
t <option value="8" 
c C B 1 2 0 %s
t >GMT+08:00 West Australian Standard Time</option>
t <option value="9" 
c C B 1 2 1 %s
t >GMT+09:00 Japan Standard Time</option>
t <option value="10" 
c C B 1 2 2 %s
t >GMT+10:00 East Australian Standard Time</option>
t <option value="11" 
c C B 1 2 3 %s
t >GMT+11:00</option>
t <option value="12" 
c C B 1 2 4 %s
t >GMT+12:00 International Date Line East</option>
t </select>
t </td></tr><tr align="center"><td class="table_data_footer" colspan="2">
t <input id="time_formats_button_save" type="submit"
t value="Apply"/>
t </td></tr></form>
t </table>
t <br>
# Manual Configuration
t <table class="table_data">
t <tr align="left"><td class="table_data_header" colspan="2">
t UTC Manual Configuration
t </td></tr><form method="post">
# Time
t <tr align="left"><td class="table_data_row" width="40%%">
t Time
t </td><td class="table_data_row">
t <input type="time" name="manual_time"/>
t </td></tr>
# Date
t <tr align="left"><td class="table_data_row">
t Date
t </td><td class="table_data_row">
t <input type="date" name="manual_date"/>
t </td></tr><tr align="center"><td class="table_data_footer" colspan="2">
t <input id="time_manual_button_save" type="submit"
t value="Apply"/>
t </td></tr></form>
t </table>
t <br>
# SNTP Configuration Header
t <table class="table_data">
t <tr align="left"><td class="table_data_header" colspan="2">SNTP Configuration</td><tr>
# SNTP Server IP 1 Row
t <tr align="left"><td class="table_data_row" width="40%%">
t SNTP Server IP 1 *
t </td><form method="post"><td class="table_data_row">
t <input name="sntp_ip_1_0" id="sntp_ip_1_0" onKeyPress="return checkKeyIfNumber(event)"
t onChange="checkTextIP(id)"
t style="width:30px;" type="text" maxlength="3"
c C C 0 0 value="%d"/> . 
t <input name="sntp_ip_1_1" id="sntp_ip_1_1" onKeyPress="return checkKeyIfNumber(event)"
t onChange="checkTextIP(id)"
t style="width:30px;" type="text" maxlength="3"
c C C 0 1 value="%d"/> . 
t <input name="sntp_ip_1_2" id="sntp_ip_1_2" onKeyPress="return checkKeyIfNumber(event)"
t onChange="checkTextIP(id)"
t style="width:30px;" type="text" maxlength="3"
c C C 0 2 value="%d"/> . 
t <input name="sntp_ip_1_3" id="sntp_ip_1_3" onKeyPress="return checkKeyIfNumber(event)"
t onChange="checkTextIP(id)"
t style="width:30px;" type="text" maxlength="3"
c C C 0 3 value="%d"/>
c C C 0 4 %s
t </td></tr>
# SNTP Server IP 2 Row
t <tr align="left"><td class="table_data_row">
t SNTP Server IP 2
t </td><td class="table_data_row">
t <input name="sntp_ip_2_0" id="sntp_ip_2_0" onKeyPress="return checkKeyIfNumber(event)"
t onChange="checkTextIP(id)"
t style="width:30px;" type="text" maxlength="3"
c C C 0 5 value="%d"/> . 
t <input name="sntp_ip_2_1" id="sntp_ip_2_1" onKeyPress="return checkKeyIfNumber(event)"
t onChange="checkTextIP(id)"
t style="width:30px;" type="text" maxlength="3"
c C C 0 6 value="%d"/> . 
t <input name="sntp_ip_2_2" id="sntp_ip_2_2" onKeyPress="return checkKeyIfNumber(event)"
t onChange="checkTextIP(id)"
t style="width:30px;" type="text" maxlength="3"
c C C 0 7 value="%d"/> . 
t <input name="sntp_ip_2_3" id="sntp_ip_2_3" onKeyPress="return checkKeyIfNumber(event)"
t onChange="checkTextIP(id)"
t style="width:30px;" type="text" maxlength="3"
c C C 0 8 value="%d"/>
c C C 0 9 %s
t </td></tr>
# SNTP Button Save
t <input name="sntp_time_load" value="yes" type="hidden"/>
t <tr align="center"><td class="table_data_footer" colspan="2">
t <input id="sntp_button_save" type="submit"
t value="Apply"/>
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
