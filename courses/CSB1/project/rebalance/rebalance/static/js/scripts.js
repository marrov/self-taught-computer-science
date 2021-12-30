/*!
    * Start Bootstrap - SB Admin v7.0.4 (https://startbootstrap.com/template/sb-admin)
    * Copyright 2013-2021 Start Bootstrap
    * Licensed under MIT (https://github.com/StartBootstrap/startbootstrap-sb-admin/blob/master/LICENSE)
    */
    // 
// Scripts
// 

window.addEventListener('DOMContentLoaded', event => {

    // Toggle the side navigation
    const sidebarToggle = document.body.querySelector('#sidebarToggle');
    if (sidebarToggle) {
        // Uncomment Below to persist sidebar toggle between refreshes
        // if (localStorage.getItem('sb|sidebar-toggle') === 'true') {
        //     document.body.classList.toggle('sb-sidenav-toggled');
        // }
        sidebarToggle.addEventListener('click', event => {
            event.preventDefault();
            document.body.classList.toggle('sb-sidenav-toggled');
            localStorage.setItem('sb|sidebar-toggle', document.body.classList.contains('sb-sidenav-toggled'));
        });
    }

});

function deleteRow(btn) {
    var row = btn.parentNode.parentNode;
    var i = row.parentNode.parentNode.rowIndex - 1;
    var rowCount = document.getElementById('assetTable').rows.length;
    if (rowCount == 1) {
        alert('This is the only row left in the table, it cannot be deleted!')
    } else {
        document.getElementById('assetTable').deleteRow(i);
    }
}

function addRow() {
    var row = document.getElementById("assetRow-0"); // find row to copy
    var table = document.getElementById("assetTable"); // find table to append to
    var rowCount = table.rows.length;
    var clone = row.cloneNode(true); // copy children too
    clone.id = "assetRow-" + rowCount; // change id or other attributes/contents

    clone.getElementsByTagName("td")[0].getElementsByTagName("select")[0].name = "fund-" + rowCount
    clone.getElementsByTagName("td")[1].getElementsByTagName("input")[0].name = "allocation-" + rowCount

    table.appendChild(clone); // add new row to end of table
}