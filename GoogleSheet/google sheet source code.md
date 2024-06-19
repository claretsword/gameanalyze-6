

function updateSpreadsheet(data) {
  var sheet = SpreadsheetApp.getActiveSpreadsheet().getActiveSheet();
  var lastRow = sheet.getLastRow();
  
  sheet.getRange(lastRow + 1, 1).setValue(data.ID);
  sheet.getRange(lastRow + 1, 2).setValue(data.단계);
  sheet.getRange(lastRow + 1, 3).setValue(data.소지금);
  sheet.getRange(lastRow + 1, 4).setValue(data.날짜);
}