var objects = [];
var mouseDown = 0;

document.body.onmousedown = function() { 
    mouseDown = 1;
}

document.body.onmouseup = function() {
    mouseDown = 0;
}

function getObjects() {
    if (!mouseDown) {
        $.ajax({
            url: "/api/dashboard/all",
            method: "GET",
            success: function(data) {
                if (!mouseDown) {
                    objects = data;
                    renderObjects();
                }
            }
        })
    } else {
        
    }
}

function renderObjects() {
    var template = $.templates("#dom_object");
    var htmlOutput = template.render(objects);
    $("#object-card-holder").html(htmlOutput);
}

function actionUpdate(obj_id, actuator, value) {
    $.ajax({
        url:"/api/dashboard/" + obj_id,
        method: "POST",
        data: {"actuator": actuator, "value": value},
        success: function(data) {
            M.toast({html: "Bijgewerkt"});
        }
    });
}

function pollNotifications(id) {
    $.ajax({
        url:"/api/interface_notifications?not_id=" + id,
        timeout: 10000,
        success: function(data) {
            console.log(data);
            data = JSON.parse(data);
            for (var i = 0; i < data.length; i++) {
                if (data[i].id == 0) {
                    $("<p class=\"flow-text white-text\" style=\"background: red\">" 
                        + data[i].time + " | " + data[i].message + "</p>").appendTo("#notification-holder");
                } else {
                    $("<p class=\"flow-text white-text\" style=\"background: blue\">" 
                        + data[i].time + " | " + data[i].message + "</p>").appendTo("#notification-holder");
                }
            }
            if (data.length > 0) {
                var elem = document.getElementById("notifications");
                var instance = M.Modal.getInstance(elem);
                instance.open();
                pollNotifications(data[data.length - 1]["not_id"]);
            } else {
                pollNotifications(id);
            }
        },
        error: function(jqXHR, textStatus, errorThrown) {
            console.log(jqXHR.status + "," + textStatus + ", " + errorThrown);
            pollNotifications(id);
        }
    });
}

function clearNotifications() {
    $("#notification-holder").empty();
}

getObjects();
setInterval(function () {
    //getObjects();
}, 1000);
