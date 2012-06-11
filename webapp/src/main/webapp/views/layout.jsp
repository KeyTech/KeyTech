<%@page contentType="text/html" pageEncoding="UTF-8" isELIgnored="false" %>
<%@taglib prefix="sec" uri="http://www.springframework.org/security/tags" %>
<!DOCTYPE html>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
		<title>KeyTech</title>
		<base href="http://${pageContext.request.serverName}:${pageContext.request.serverPort}${pageContext.request.contextPath}/" />

		<link rel="stylesheet" href="resources/css/screen.css" type="text/css" media="screen" title="default" />
		<link type="text/css" href="resources/css/custom-theme/jquery-ui-1.8.21.custom.css" rel="stylesheet" />

		<script type="text/javascript" src="resources/js/jquery/jquery-1.7.2.js"></script>
		<script type="text/javascript" src="resources/js/jquery/jquery-ui-1.8.21.js"></script>
		<script type="text/javascript" src="resources/js/application.js"></script>
	</head>
	<body> 
		<div id="page-top-outer">
			<div id="page-top">
				<div id="logo">
					<a href="">
						<img src="resources/images/shared/logo.png" width="156" height="40" alt="" />
					</a>
				</div>
			</div>
		</div>

		<div class="nav-outer-repeat"> 
			<div class="nav-outer"> 

				<div id="nav-right">

					<div class="nav-divider">&nbsp;</div>
					<sec:authorize access="isAuthenticated()">
					<a href="j_spring_security_logout" id="logout">
						<img src="resources/images/shared/nav/nav_logout.gif" width="14" height="14" alt="" /> Logout
					</a>
					</sec:authorize>
					<sec:authorize access="isAnonymous()">
					<a href="login" id="logout">
						<img src="resources/images/shared/nav/nav_logout.gif" width="14" height="14" alt="" /> Login
					</a>
					</sec:authorize>					
				</div>

				<div class="nav">
					<div class="table">
					</div>

					<ul class="select"><li><a href="#nogo"><b>Dashboard</b></a>
							<div class="select_sub">
								<ul class="sub">
									<li><a href="#nogo">Dashboard Details 1</a></li>
									<li><a href="#nogo">Dashboard Details 2</a></li>
									<li><a href="#nogo">Dashboard Details 3</a></li>
								</ul>
							</div>
						</li>
					</ul>

					<div class="nav-divider">&nbsp;</div>

					<ul class="current"><li><a href="reservation"><b>Reserveringen</b></a>
							<div class="select_sub show">
								<ul class="sub">
									<li><a href="reservation">Overzicht</a></li>
									<li><a href="reservation/create">Nieuwe reservering toevoegen</a></li>
								</ul>
							</div>
						</li>
					</ul>

					<div class="nav-divider">&nbsp;</div>

					<ul class="select"><li><a href="#nogo"><b>Categories</b></a>
							<div class="select_sub">
								<ul class="sub">
									<li><a href="#nogo">Categories Details 1</a></li>
									<li><a href="#nogo">Categories Details 2</a></li>
									<li><a href="#nogo">Categories Details 3</a></li>
								</ul>
							</div>
						</li>
					</ul>

					<div class="nav-divider">&nbsp;</div>

					<ul class="select"><li><a href="#nogo"><b>Clients</b></a>
							<div class="select_sub">
								<ul class="sub">
									<li><a href="#nogo">Clients Details 1</a></li>
									<li><a href="#nogo">Clients Details 2</a></li>
									<li><a href="#nogo">Clients Details 3</a></li>

								</ul>
							</div>
						</li>
					</ul>
				</div>
			</div>
		</div>
		</div>

		<div id="content-outer">
			<div id="content">
				<jsp:include page="${contentPage}" />
			</div>
		</div>

		<div id="footer">
			<div id="footer-left">KeyTech administration panel</div>
			<div class="clear">&nbsp;</div>
		</div>
	</body>
</html>