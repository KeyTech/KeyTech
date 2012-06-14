<%@page isELIgnored="false" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<base href="http://${pageContext.request.serverName}:${pageContext.request.serverPort}${pageContext.request.contextPath}/" />
		<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
		<title>KeyTech</title>
		<link rel="stylesheet" href="resources/css/screen.css" type="text/css" media="screen" title="default" />

		<script src="resources/js/jquery/jquery-1.7.2.js" type="text/javascript"></script>
		<script src="resources/js/jquery/custom_jquery.js" type="text/javascript"></script>
	</head>
	<body id="login-bg">

		<div id="login-holder">

			<div id="logo-login">
				<a href="index.html"><img src="resources/images/shared/logo.jpg" width="156" height="40" alt="" /></a>
			</div>

			<div class="clear"></div>

			<div id="loginbox">
				<form action="j_spring_security_check" method="post">
					<div id="login-inner">
						<table border="0" cellpadding="0" cellspacing="0">
							<tr>
								<th>Username</th>
								<td><input type="text" name="j_username" class="login-inp" /></td>
							</tr>
							<tr>
								<th>Password</th>
								<td><input type="password" name="j_password" class="login-inp" /></td>
							</tr>
							<tr>
								<th></th>
								<td valign="top"><input type="checkbox" class="checkbox-size" id="login-check" /><label for="login-check">Remember me</label></td>
							</tr>
							<tr>
								<th></th>
								<td><input type="submit" class="form-submit" value="Inloggen" /></td>
							</tr>
						</table>
					</div>
				</form>
			</div>
		</div>
	</body>
</html>