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

window.addEventListener('DOMContentLoaded', event => {

    // Add table row when click btn
    const addAssetRow = document.getElementById('addAssetRow');
    addAssetRow.addEventListener('click', event => {
        const assetTable = document.getElementById('assetTable');
        const assetRow = document.getElementById('assetRow');
        const newRow = assetRow.cloneNode(true);
        assetTable.appendChild(newRow);
    });

    // Delete table row when click btn
    const deleteAssetRow = document.getElementById('deleteAssetRow');
    deleteAssetRow.addEventListener('click', event => {
        const assetTable = document.getElementById('assetTable');
        assetTable.removeChild(assetTable.lastElementChild);
    });

});