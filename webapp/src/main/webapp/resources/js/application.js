$(document).ready(function () {
	$(".datepicker").datepicker({
		dateFormat: "dd-mm-yy"
	});
	
	currentUrl = String(window.location).replace($("base").attr("href"), "");
	$("ul.sub li").each(function() {
		if($(this).children("a").attr("href") == currentUrl) {
			$(this).addClass("sub_show");
		}
	});
	
	autoComplete(".room-autocomplete", "room/searchAjax/?query=", function(item) {
		return item.roomName;
	});
	
		
	autoComplete(".group-autocomplete", "group/searchAjax/?query=", function(item) {
		return item.groupName;
	});
	
	autoComplete(".add-user", "user/searchAjax/?query=", function(item) {
		return item.firstname + " " + item.lastname + " (" + item.userIdentifier + ")";
	});
	
	$(function () {
		userIdentifiers = new Array();
		groupMode = 'create';
		
		$(".edit-button").click(function () {
			$("tr.user-row").remove();
			userIdentifiers = new Array();
			$.ajax("group/get", {
				type: "get",
				data: {
					groupName: $("#group").val()
				}, 
				dataType: "json",
				success: function (response) {
					var title;
					$(".add-user").val('');
					if(response !== null) {
						groupMode = 'update';
						title = 'Groep bewerken';
						$(".groupname").val(response.groupName);
						$(".expirationDate").datepicker('setDate', $.datepicker.parseDate('@',response.expirationDate));
						$(".groupname").attr('disabled', 'disabled');
						for(var index in response.users) {
							var user = response.users[index];
							addUserToGroup(user.firstname + " " + user.lastname + " (" + user.userIdentifier + ")");
						}
					} else {
						groupMode = 'create';
						title = 'Nieuwe groep maken';
						$(".expirationDate").val('');
						$(".groupname").val($("#group").val());
						$(".groupname").removeAttr('disabled');
					}
					$("#create-group-dialog").dialog({
						resizable: false,
						width: 354,
						modal: true,
						title: title
					});
				}
			});
			return false;
		});
	
		$(".add-user").autocomplete({
			select: function(event, ui) {
				addUserToGroup(ui.item.value);
			}
		});
		
		$("#users").parent().delegate("tr.user-row", "click", function() {
			userIdentifiers.splice(userIdentifiers.indexOf($(this).children(".userIdentifier").val()), 1);
			$(this).remove();
		});
	
		function addUserToGroup(user) {
			var location = user.lastIndexOf("(") + 1;
			var userIdentifier = user.substr(location, user.lastIndexOf(")") - location);
		
			$(".add-user").select();

			if(userIdentifiers.indexOf(userIdentifier) != -1) {
				showError("Gebruiker zit al in deze groep.");
				return;
			}
		
			$(	'<tr class="user-row"><td colspan="2">' +
				'<div class="user">' + user + '</div>' +
				'<input type="hidden" class="userIdentifier" value="' + userIdentifier + '" />' +
				'</td></tr>')
			.insertAfter("#users");
			
			userIdentifiers.push(userIdentifier);
			hideError();
		}
		
		function showError(error) {
			$(".user-add-error").show();
			$(".user-add-error").children().html(error);
		}
		
		function hideError() {
			$(".user-add-error").hide();			
		}
		
		$(".save-group").click(function() {
			var date = $(".expirationDate").val().split("-");
			var format = new Date(date[2], date[1] - 1, date[0]);
			var group = {
				groupName: $(".groupname").val(),
				expirationDate: format.toJSON(),
				users: $.map(userIdentifiers, function(userIdentifier) {
					return {
						"userIdentifier" : userIdentifier
					};
				})
			};
			var alreadyExists = false;
			
			if(groupMode == 'create') {
				$.ajax("group/get", {
					type: "get",
					data: {
						groupName: group.groupName
					}, 
					dataType: "json",
					success: function (response) {
						if(response !== null) {
							alreadyExists = true;
						}
					},
					async: false
				});
			}
			
			if(alreadyExists) {
				showError("Groepsnaam is niet uniek.");
				return;
			}
				
			$.ajax("group/save", {
				type: "post",
				data: JSON.stringify(group), 
				contentType: "application/json", 
				dataType: "json",
				success: function (response) {
					if(response.success === false) {
						showError(response.message);
					} else {
						$("#group").val($(".groupname").val());
						$("#create-group-dialog").dialog("close");
					}
				}
			});
		});
	});
	
	$(function() {
		$(".message-green").click(function() {
			$(this).hide({
				duration: 400, 
				effect: "clip"
			});
		});
	});

	$(function() {
		$(".reservation-delete").click(function () {
			var $row = $(this).parent().parent()
			$.getJSON($(this).attr("href"), null, function(result) {
				if(result.success) {
					$row.hide();
				}
			});
			
			return false;
		});
	});

	function autoComplete(selector, source, responseCallback) {
		var cache = new Array();
		
		$(selector).autocomplete({
			source: function(request, response) {
				if(request.term in cache) {
					response(cache[request.term]);
					return;
				}
				
				$.getJSON(source + request.term, null, function(data) {
					cache[request.term] = $.map(data, responseCallback);
					response(cache[request.term]);
				});
			},
			minLength: 0
		});
	};
});