function start() {
  $("#title").html(GetMessage());
}

function changeLoadMode(mode) {
  console.log(mode);
  $("#load_settings > div").each(function (e) {
    if ($(this).attr("id") == mode) $(this).show();
    else $(this).hide();
  });
}

$(document).ready(function () {
  changeLoadMode($("#load_mode").val());
  $("#load_mode").on("change", function (e) {
    changeLoadMode($(this).val());
  });
});
