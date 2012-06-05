<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@ taglib prefix="spring" uri="http://www.springframework.org/tags"%>
<%@taglib uri="http://www.springframework.org/tags/form" prefix="form"%>
<div id="page-heading"><h1>Reserveringen</h1></div>

<table border="0" width="100%" cellpadding="0" cellspacing="0" id="content-table">
	<tr>
		<th rowspan="3" class="sized"><img src="resources/images/shared/side_shadowleft.jpg" width="20" height="300" alt="" /></th>
		<th class="topleft"></th>
		<td id="tbl-border-top">&nbsp;</td>
		<th class="topright"></th>
		<th rowspan="3" class="sized"><img src="resources/images/shared/side_shadowright.jpg" width="20" height="300" alt="" /></th>
	</tr>
	<tr>
		<td id="tbl-border-left"></td>
		<td>
			<div id="content-table-inner">
				<c:if test="${not empty message}">
					<div class="message-green"><spring:message code="${message}" /></div>
				</c:if>
				<form:form method="get" modelAttribute="form" action="reservation">
					<table border="0" cellpadding="0" cellspacing="0"  id="id-form">
						<tr>
							<th valign="top"><form:label path="room">Ruimte:</form:label></th>
							<td><form:select items="${rooms}" itemValue="roomName" itemLabel="roomName" path="room" cssClass="styledselect" /></td>
							<th valign="top"><form:label path="startDate">Datum:</form:label></th>
							<td>
								<form:input path="startDate" cssClass="datepicker inp-form" />
								<strong><form:label path="endDate"> tot </form:label></strong>
								<form:input path="endDate" cssClass="inp-form datepicker" />
							</td>
							<td><input type="submit" value="Reserveringen" class="form-submit" /></td>
						</tr>
					</table>					
				</form:form>
				<table border="0" width="100%" cellpadding="0" cellspacing="0" id="product-table">
					<tr>
						<th class="table-header-check"><a id="toggle-all" ></a> </th>
						<th class="table-header-repeat line-left">Ruimte</th>
						<th class="table-header-repeat line-left">Groep</th>
						<th class="table-header-repeat line-left">Start Datum</th>
						<th class="table-header-repeat line-left">Eind Datum</th>
						<th class="table-header-repeat line-left">Interval</th>
						<th class="table-header-repeat line-left">Tijd</th>

						<th class="table-header-options line-left">Options</th>
					</tr>

					<c:forEach items="${reservations}" var="reservation">
						<tr class="alternate-row">
							<td></td>
							<td>${reservation.room.roomName}</td>
							<td>${reservation.group.groupName}</td>
							<td><spring:eval expression="reservation.startDate" /></td>
							<td><spring:eval expression="reservation.endDate" /></td>
							<td>${reservation.interval}</td>
							<td>${reservation.reservationTime.startTime} - ${reservation.reservationTime.endTime}</td>
							<td class="options-width">
								<a href="reservation/update/${reservation.reservationIdentifier}" title="Wijzigen" class="icon-1 info-tooltip"></a>
								<a href="reservation/delete?reservation=${reservation.reservationIdentifier}" title="Verwijderen" class="icon-2 info-tooltip reservation-delete"></a>
							</td>
						</tr>
					</c:forEach>
				</table>
			</div>
		</td>
		<td id="tbl-border-right"></td>
	</tr>
	<tr>
		<th class="sized bottomleft"></th>
		<td id="tbl-border-bottom">&nbsp;</td>
		<th class="sized bottomright"></th>
	</tr>
</table>