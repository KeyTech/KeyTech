<%@page isELIgnored="false" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<base href="http://${pageContext.request.serverName}:${pageContext.request.serverPort}${pageContext.request.servletContext.contextPath}/" />
		<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
		<title>KeyTech</title>
		<link rel="stylesheet" href="resources/css/screen.css" type="text/css" media="screen" title="default" />

		<script src="resources/js/jquery/jquery-1.7.2.js" type="text/javascript"></script>
		<script src="resources/js/jquery/custom_jquery.js" type="text/javascript"></script>
	</head>
	<body id="login-bg">

		<div id="login-holder">

			<div id="logo-login">
				<a href="index.html"><img src="resources/images/shared/logo.png" width="156" height="40" alt="" /></a>
			</div>

			<div class="clear"></div>

			<div id="loginbox">

				<div id="login-inner">
					<table border="0" cellpadding="0" cellspacing="0">
						<tr>
							<th>Username</th>
							<td><input type="text"  class="login-inp" /></td>
						</tr>
						<tr>
							<th>Password</th>
							<td><input type="password" value="************"  onfocus="this.value=''" class="login-inp" /></td>
						</tr>
						<tr>
							<th></th>
							<td valign="top"><input type="checkbox" class="checkbox-size" id="login-check" /><label for="login-check">Remember me</label></td>
						</tr>
						<tr>
							<th></th>
							<td><input type="button" class="submit-login"  /></td>
						</tr>
					</table>
				</div>
			</div>
		</div>
	</body>
</html>