/**
 * 
 */
require.config({

  baseUrl: '/js',
  paths: {

    "jquery": "jquery",
    "pagization": "pagization",
    "template": "template",
    "layui": "layui/layui.all",
    "datepicker":"DatePicker",
    "dboper": "DBOper",
    'wangEditor.min': 'wangEditor.min',
    "plupload": 'plupload-2.1.2/js/plupload.full.min',
    "pop": "Popup",
    'editor':'Editor',
    'downloader':'Downloader',
    "uploader": "Uploader",
    "inputwidgets": 'InputWidgets',
    'dataverifier': 'DataVerifier',
    'eventCenter': 'EventCenter',
    

    "index": "Index",
    'inputborder': 'index/InputBorder',
    'recordlist': 'index/RecordList',
    "login": "LoginJs",
    "admin": "Admin",
    
  }, 

  shim: {
    'plupload': {
      deps: ['jquery'],
      exports: 'plupload'
    },
    "layui": {
      exports: 'layui'
    }

  }

});


require(["jquery"], function ($) {

    var currentPage = $("#current-page").attr("current-page");
    var targetModule = $("#current-page").attr("target-module");
    //console.log(targetModule);
    switch( targetModule ){
      case 'index':
        require(['index'], function (test) {
          new test( $('body') ).init();
        });
        break;
      case 'login':
        require(['login'], function (test) {
          new test( $('body') ).init();
        });
        break;
      case 'admin':
          require(['admin'], function (test) {
            new test( $('body') ).init();
          });
          break;
    }
    return;
  });