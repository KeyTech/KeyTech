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
		
		$(".add-user").autocomplete({
			select: function() {
				addUserToGroup();
			}
		});
		
		$("#users").parent().delegate("tr.user-row", "click", function() {
			$(this).remove();
		});
	
		function addUserToGroup() {
			var label = $(".add-user").val();
			var location = label.lastIndexOf("(") + 1;
			var userIdentifier = label.substr(location, label.lastIndexOf(")") - location);
		
			$(".add-user").select();

			if(userIdentifiers.indexOf(userIdentifier) != -1) {
				showError("Gebruiker zit al in deze groep.");
				return;
			}
		
			$(	'<tr class="user-row"><td colspan="2">' +
					'<div class="user">' + label + '</div>' +
					'<input type="hidden" class="userIdentifier" value="' + userIdentifier + '" />' +
				'</td></tr>')
			.insertAfter("#users");
			
			userIdentifiers.push(userIdentifier);
		}
		
		function showError(error) {
			$(".user-add-error").show();
			$(".user-add-error").children().html(error);
		}
		
		$(".save-group").click(function() {
			var group = {
				groupName: $(".groupname").val(),
				users: userIdentifiers
			};
			
			console.log(group);
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
	
	$(".edit-button").click(function () {
		$("#create-group-dialog").dialog({
			resizable: false,
			width: 354,
			modal: true
		});
		return false;
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