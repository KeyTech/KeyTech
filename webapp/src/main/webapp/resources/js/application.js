$(document).ready(function () {
	$(".datepicker").datepicker({
		dateFormat: "dd-mm-yy"
	});
	
	console.log(String(window.location).replace($("base").attr("href"), ""));
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
	
	$(function() {
		$(".message-green").click(function() {
			$(this).hide({duration: 400, effect: "clip"});
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
});