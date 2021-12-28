window.addEventListener('DOMContentLoaded', event => {
    // Simple-DataTables
    // https://github.com/fiduswriter/Simple-DataTables/wiki

    const datatablesSimple = document.getElementById('datatablesSimple');
    if (datatablesSimple) {
        new simpleDatatables.DataTable(datatablesSimple);
    }

    const datatablesDynamic = document.getElementById('datatablesDynamic');
    if (datatablesDynamic) {
        new simpleDatatables.DataTable(datatablesDynamic, {
            searchable: false,
            sortable: false,
            layout: {
                top: "",
                bottom: ""
            },
        });
    }

});