<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@taglib uri="http://www.springframework.org/tags/form" prefix="form"%>
<div id="create-group-dialog" title="Nieuwe groep">
	<table border="0" cellpadding="0" cellspacing="0"  id="id-form">
		<tr class="user-add-error">
			<td colspan="2"></td>
		</tr>
		<tr>
			<th valign="top">Groepsnaam:</th>
			<td><input type="text" class="groupname inp-form" /></td>
		</tr>	
		<tr>
			<th valign="top">Vervaldatum:</th>
			<td><input type="text" class="expirationDate datepicker inp-form" /></td>
		</tr>	
		<tr id="users">
			<th valign="top">Leden:</th>
		</tr>
		<tr>
			<td colspan="2">
				<input type="text" name="user" class="add-user inp-form" />
			</td>
		</tr>
		<tr>
			<td colspan="2" style="text-align: right;">
				<input type="submit" value="Opslaan" class="save-group form-submit" />
			</td>
		</tr>
	</table>
</div>

<div id="page-heading">
	<h1>
		<c:choose>
			<c:when test="${reservation.reservationIdentifier == null}">Nieuwe reservering</c:when>
			<c:otherwise>Wijzigen reservering</c:otherwise>
		</c:choose>
	</h1>
</div>

<form:form method="post" modelAttribute="reservation">
	<form:hidden path="reservationIdentifier" />
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
				<!--  start content-table-inner -->
				<div id="content-table-inner">
					<form:errors cssClass="error-inner" cssStyle="margin-bottom: 10px;" />

					<table border="0" width="100%" cellpadding="0" cellspacing="0">
						<tr valign="top">
							<td>
								<table border="0" cellpadding="0" cellspacing="0"  id="id-form">
									<tr>
										<th valign="top">Ruimte:</th>
										<td><form:input path="room" cssClass="inp-form room-autocomplete" /></td>
										<td>
											<form:errors path="room" cssClass="error-inner" />
										</td>
									</tr>
									<tr>
										<th valign="top">Groep:</th>
										<td>
											<form:input path="group" cssClass="inp-form group-autocomplete" disabled="${reservation.reservationIdentifier != null}" />													
											<c:if test="${reservation.reservationIdentifier != null}">
												<form:hidden path="group" />													
											</c:if>
											<a class="edit-button group-edit" href="#"></a>
										</td>
										<td>
											<form:errors path="group" cssClass="error-inner" />
										</td>
									</tr>
									<tr>
										<th valign="top">Begindatum:</th>
										<td>	
											<form:input path="startDate" cssClass="inp-form datepicker" />
										</td>
										<td>
											<form:errors path="startDate" cssClass="error-inner" />
										</td>
									</tr>
									<tr>
										<th valign="top">Einddatum:</th>
										<td>
											<form:input path="endDate" cssClass="inp-form datepicker" />
										</td>
										<td>
											<form:errors path="endDate" cssClass="error-inner" />
										</td>
									</tr>
									<tr>
										<th valign="top">Interval:</th>
										<td>
											<form:select path="interval" cssClass="styledselect">
												<form:option value="DAY">Dagelijks</form:option>
												<form:option value="WEEK">Wekelijks</form:option>
											</form:select>
										</td>
										<td>
											<form:errors path="interval" cssClass="error-inner" />
										</td>
									</tr>
									<tr>
										<th valign="top">Tijdsspanne:</th>
										<td>
											<form:select path="reservationTime" items="${reservationTimes}" itemLabel="name" itemValue="name" cssClass="styledselect" />
										</td>
										<td>
											<form:errors path="reservationTime" cssClass="error-inner" />
										</td>
									</tr>
									<tr>
										<th>&nbsp;</th>
										<td valign="top">
											<input type="submit" value="Opslaan" class="form-submit" />
											<input type="reset" value="Reset" class="form-reset"  />
										</td>
										<td></td>
									</tr>
								</table>
							</td>
						</tr>
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
</form:form>