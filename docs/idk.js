$("form").on("submit", function(){
    url = $(this).attr("action"),
    method = $(this).attr("method"),
    $.ajax({
	url: url,
	type: method,
	dataType: 'jsonp',
    }
	  );
    return false;
});
