const BLOCK_HTML =
  '<td><div class="block"><div class="block-inside block-cover"><div class="block-field"></div></div></td>';

// function GetBoardWidth() {
//   return 9;
// }

// function GetBoardHeight() {
//   return 9;
// }

// function LoadBoard() {
//   return true;
// }

// function BoardStartGame() {
//   return true;
// }

// function GetBoardGameState() {
//   return "Playing";
// }

// function BoardAction(x, y, right_click) {
//   return true;
// }

// function GetBoardFieldInChar(x, y) {
//   return "#";
// }

function charToInt(char) {
  return char.charCodeAt(0);
}

function intToChar(int) {
  return String.fromCharCode(int);
}

function winAnimation() {
  win_bgm.currentTime = 0;
  win_bgm.play();
  $("#result-title").html("You<br>Win");
  $("#result-title").css("fontSize", "100px");
  $("#result").fadeIn("fast");
  $("#result-title").animate(
    { fontSize: "150px" },
    {
      complete: function () {
        $("#result").delay(1000).fadeOut("slow");
      },
    }
  );
}

function loseAnimation() {
  bgm.pause();
  win_bgm.pause();
  $("#result-title").html(`<i class="fa-solid fa-bomb"></i>`);
  $("#result-title").css("fontSize", "100px");
  let warning = new Audio("./audio/warning.mp3");
  warning.play();
  $("#result").fadeIn("fast");
  $("#result-title")
    .animate({ fontSize: "300px" })
    .animate({ marginLeft: "30px", marginRight: "0px" }, 100)
    .animate({ marginLeft: "0px", marginRight: "30px" }, 100)
    .animate({ marginLeft: "30px", marginRight: "0px" }, 100)
    .animate({ marginLeft: "0px", marginRight: "30px" }, 100)
    .animate({ marginLeft: "30px", marginRight: "0px" }, 100)
    .animate({ marginLeft: "0px", marginRight: "30px" }, 100)
    .animate({ marginLeft: "30px", marginRight: "0px" }, 100)
    .animate({ marginLeft: "0px", marginRight: "30px" }, 100)
    .animate({ marginLeft: "30px", marginRight: "0px" }, 100)
    .animate(
      { marginLeft: "0px", marginRight: "30px" },
      {
        duration: 100,
        complete: function () {
          warning.pause();
          let audio = new Audio("./audio/bomb.mp3");
          audio.play();
        },
      }
    )
    .animate({ marginLeft: "0px", marginRight: "0px" }, 100)
    .animate(
      { fontSize: "9999px" },
      {
        complete: function () {
          $("#result").fadeOut();
        },
      }
    );
}

let bgm = new Audio("./audio/bgm.mp3");
let win_bgm = new Audio("./audio/win.mp3");

function load() {
  console.log("load");
  let success = false;
  let width, height;
  switch ($("#load_mode").val()) {
    case "file":
      load_mode = 0;
      success = LoadBoard(0, $('input[name="filename"]').val());
      break;
    case "random_count":
      width = $('input[name="width"]').val();
      height = $('input[name="height"]').val();
      let mines_count = $('input[name="mines_count"]').val();
      success = LoadBoard(1, width, height, mines_count);
      break;
    case "random_rate":
      width = $('input[name="width"]').val();
      height = $('input[name="height"]').val();
      let mines_rate = $('input[name="mines_rate"]').val();
      success = LoadBoard(2, width, height, mines_rate);
      break;
  }
  if (!success) bootbox.alert("加載失敗！");
  //   bootbox.alert(success ? "加載成功！" : "加載失敗！");
}

function generateBoard(width, height) {
  let board = $("#board");
  board.find("tbody").empty();
  for (let i = 0; i < height; i++) {
    let tr = $("<tr></tr>");
    board.find("tbody").append(tr);
    for (let j = 0; j < width; j++) {
      let x = j;
      let y = i;
      let td = $(BLOCK_HTML);
      let block = td.find("div.block");
      block.attr("ms-block-x", x);
      block.attr("ms-block-y", y);
      tr.append(td);
      block.on("mousedown", function (event) {
        if (GetBoardGameState() == "GameOver") {
          bootbox.dialog({
            title: GetBoardWin() == "Win" ? "你已經獲勝！" : "你已經失敗！",
            message: "<p>遊戲已經結束，你可以選擇重玩</p> ",
            size: "large",
            buttons: {
              cancel: {
                label: "不要",
                className: "btn-danger",
              },
              ok: {
                label: "重玩",
                className: "btn-primary",
                callback: function () {
                  BoardReplay();
                  showStartDialog();
                  bgm.pause();
                  win_bgm.pause();
                },
              },
            },
          });
        } else {
          let x = parseInt($(this).attr("ms-block-x"));
          let y = parseInt($(this).attr("ms-block-y"));
          let success = false;
          switch (event.which) {
            case 1: // Left Click
              console.log(`Left Click x=${x}, y=${y}`);
              success = leftClick(x, y);
              updateBoard();
              if (success) {
                if (GetBoardGameState() == "GameOver") {
                  bgm.pause();
                  if (GetBoardWin() == "Lose") {
                    loseAnimation();
                  } else {
                    winAnimation();
                  }
                } else {
                  let audio = new Audio("./audio/click.mp3");
                  audio.play();
                }
              }
              break;
            case 3: // Right Click
              console.log(`Right Click x=${x}, y=${y}`);
              success = rightClick(x, y);
              updateBoard();
              break;
          }
        }
      });
    }
  }
}

function start() {
  load();
  let success = BoardStartGame();
  //   bootbox.alert(success ? "開始成功！" : "開始失敗！");
  if (!success) return;

  let width = GetBoardWidth();
  let height = GetBoardHeight();
  //   bootbox.alert(`Width=${width}, Height=${height}`);
  generateBoard(width, height);
  start_dialog.modal("hide");
  win_bgm.pause();
  bgm.currentTime = 0;
  bgm.play();
}

function leftClick(x, y) {
  return BoardAction(x, y, false);
}

function rightClick(x, y) {
  return BoardAction(x, y, true);
}

function updateBoard() {
  $("#board > tbody div.block").each(function (i) {
    let x = parseInt($(this).attr("ms-block-x"));
    let y = parseInt($(this).attr("ms-block-y"));
    let c = GetBoardFieldInChar(x, y);
    let block_inside = $(this).find("div.block-inside");
    let field = block_inside.find("div.block-field");
    if (c == charToInt("#") || c == charToInt("f") || c == charToInt("?")) {
      block_inside.addClass("block-cover");
      if (c == charToInt("f")) field.html(`<i class="fa-solid fa-flag"></i>`);
      else if (c == charToInt("?"))
        field.html(`<i class="fa-solid fa-question"></i>`);
      else field.empty();
    } else {
      block_inside.removeClass("block-cover");
      if (c == charToInt("X")) {
        field.html(`<i class="fa-solid fa-bomb"></i>`);
        block_inside.addClass("block-inside-mine");
      } else if (c != charToInt("0")) {
        field.text(intToChar(c));
        if (c == charToInt("1")) block_inside.addClass("block-inside-one");
        else if (c == charToInt("2")) block_inside.addClass("block-inside-two");
        else if (c == charToInt("3"))
          block_inside.addClass("block-inside-three");
        else block_inside.addClass("block-inside-four");
      }
    }
  });
}

function changeLoadMode(mode) {
  console.log(mode);
  $("#load_settings > div").each(function (i) {
    if ($(this).attr("id") == mode) $(this).show();
    else $(this).hide();
  });
}

let start_dialog;

function onStartDialogShow() {}

function showStartDialog() {
  start_dialog.modal("show");
  onStartDialogShow();
}

$(document).ready(function () {
  start_dialog = bootbox.dialog({
    title: "MineSweeper",
    message: `<div class="container-fluid">
        <div style="margin-top: 6px;">
            <label for="load_mode" class="form-label">盤面模式</label>
            <select class="form-select form-select" id="load_mode" aria-label="盤面模式" onchange="changeLoadMode($(this).val());">
                <option value="file" selected>加載盤面檔</option>
                <option value="random_count">隨機數量炸彈</option>
                <option value="random_rate">隨機概率炸彈</option>
            </select>
        </div>
        <div id="load_settings" style="margin-top: 6px;">
            <div class="row" id="file" style="display:none;">
                <div class="col">
                    <label for="filename" class="form-label">盤面檔案</label>
                    <input type="text" class="form-control" name="filename" id="filename" placeholder="盤面檔案"
                        aria-label="盤面檔案" maxlength="1023" value="board.txt">
                </div>
            </div>
            <div class="row" id="random_count" style="display:none;">
                <div class="col">
                    <label for="width" class="form-label">高度</label>
                    <input type="number" class="form-control" name="width" id="width" placeholder="高度" aria-label="高度"
                        value="10">
                </div>
                <div class="col">
                    <label for="height" class="form-label">寬度</label>
                    <input type="number" class="form-control" name="height" id="height" placeholder="寬度" aria-label="寬度"
                        value="10">
                </div>
                <div class="col">
                    <label for="mines_count" class="form-label">炸彈數量</label>
                    <input type="number" class="form-control" name="mines_count" id="mines_count" placeholder="炸彈數量"
                        aria-label="炸彈數量" value="10">
                </div>
            </div>
            <div class="row" id="random_rate" style="display:none;">
                <div class="col">
                    <label for="width" class="form-label">高度</label>
                    <input type="number" class="form-control" name="width" id="width" placeholder="高度" aria-label="高度"
                        value="10">
                </div>
                <div class="col">
                    <label for="height" class="form-label">寬度</label>
                    <input type="number" class="form-control" name="height" id="height" placeholder="寬度" aria-label="寬度"
                        value="10">
                </div>
                <div class="col">
                    <label for="mines_rate" class="form-label">炸彈概率</label>
                    <input type="number" class="form-control" name="mines_rate" id="mines_rate" placeholder="炸彈概率"
                        aria-label="炸彈概率" value="0.3">
                </div>
            </div>
        </div>
        <div style="margin-top: 6px;">
            <!-- <button type="button" class="btn btn-secondary" id="load" onclick="load();">加載盤面</button> -->
            <button type="button" class="btn btn-primary" id="start" onclick="start();">開始遊戲</button>
        </div>
    </div>`,
    closeButton: false,
    onShow: function () {
      changeLoadMode($("#load_mode").val());
    },
  });
});
