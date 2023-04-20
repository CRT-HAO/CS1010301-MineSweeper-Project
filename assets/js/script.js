function load() {
  console.log("load");
  var success = false;
  switch ($("#load_mode").val()) {
    case "file":
      load_mode = 0;
      success = LoadBoard(0, $('#id, input[name="filename"]').val());
      break;
    case "random_count":
      break;
    case "random_rate":
      break;
  }
  $("#message").html(success ? "Success" : "Failed");
}

function start() {
  $("#title").html(GetMessage());
}

function changeLoadMode(mode) {
  console.log(mode);
  $("#load_settings > div").each(function (i) {
    if ($(this).attr("id") == mode) $(this).show();
    else $(this).hide();
  });
}

$(document).ready(function () {
  changeLoadMode($("#load_mode").val());
  $("#load_mode").on("change", function (e) {
    changeLoadMode($(this).val());
  });
  $("#load").on("click", load);
});
