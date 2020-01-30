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
    } 
}

function renderObjects() {
    var template = $.templates("#dom_object");
    var htmlOutput = template.render(objects);
    $("#object-card-holder").html(htmlOutput);

    var range = new RangeTouch('input[type="range"]', {});
    $('input[type="range"]').change(function () {
        var val = $(this).val();
        console.log(val);
        actionUpdate(5, "led", val);
    }).bind("touchstart", function() {
        mouseDown = true;
    }).bind("touchend", function() {
        mouseDown = false;
    });
}

function actionUpdate(obj_id, actuator, value) {
    $.ajax({
        url:"/api/dashboard/" + obj_id,
        method: "POST",
        data: {"actuator": actuator, "value": value},
        success: function(data) {
            Materialize.toast('Bijgewerkt', 4000) // 4000 is the duration of the toast
        }
    });
    mouseDown = false;
}

function pollNotifications() {
    $.ajax({
        url:"/api/interface_notifications",
        timeout: 10000,
        success: function(data) {
            console.log(data);
            data = JSON.parse(data);
            for (var i = 0; i < data.length; i++) {
                if (data[i].id == 0 || data[i].id == 9) {
                    $("<p class=\"flow-text white-text\" style=\"background: red\">" 
                        + data[i].time + " | " + data[i].message + "</p>").appendTo("#notification-holder");
                } else {
                    $("<p class=\"flow-text white-text\" style=\"background: blue\">" 
                        + data[i].time + " | " + data[i].message + "</p>").appendTo("#notification-holder");
                }
            }
            if (data.length > 0) {
                $("#notifications").modal("open");
                console.log("opened modal");
                pollNotifications();
            } else {
                pollNotifications();
            }
        },
        error: function(jqXHR, textStatus, errorThrown) {
            console.log(jqXHR.status + "," + textStatus + ", " + errorThrown);
            setTimeout(pollNotifications, 500);
        }
    });
}

function clearNotifications() {
    $("#notification-holder").empty();
}

getObjects();
setInterval(function () {
    getObjects();
}, 500);
