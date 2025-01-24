define(
    ["template", 'inputborder', 'eventCenter', 'recordlist'],
    function (template, inputborder, ec, rc) {
        function Index(container) {
            this.container = container;
            this.ec = new ec('debug');
            this.name = 'Index';
            this.ec.addHandler(this);
            
            var _that = this;
            this.init = function () {
                this.container.find('#admin').click(function () {
                    window.location.href = '/admin';
                });

                this.container.find('#list').css('height', $('#right').height() - 32 + 'px');

                this.container.find('#right .buttons span').click(function () {
                    var cls = $(this).hasClass('active');
                    _that.container.find('#right .buttons span').removeClass('active');
                    _that.container.find('#inputborder, #configborder').hide();

                    switch ($(this).find('i').attr('id')) {
                        case 'upload':
                            break;
                        case 'export':
                            break;
                        case 'edit':
                            if( cls ){
                                _that.container.find('#inputborder').css('display', 'none');
                            }else{
                                _that.container.find('#inputborder').css('display', 'flex');
                                $(this).addClass('active');   
                                _that.ec.fire(
                                    'Index',
                                    'clear',
                                    {  }
                                );
                            }
                                
                            break;
                        case 'config':
                            if( cls ){
                                _that.container.find('#configborder').css('display', 'none');
                            }else{
                                $(this).addClass('active');   
                                _that.container.find('#configborder').css('display', 'flex');
                            }
                            break;
                    }
                });

                var tableTpl = '{{each list as data}}<div guid="{{data.guid}}" class="form-group" style="width: 100%;"><input type="submit" value="{{ data.tableName }}"  /></div>{{/each}}';
                $.post(
                    '/table/getTableList',
                    function(data){
                        var t = {}; t.list = data;
                        _that.container.find('#tables').append(template.compile(tableTpl)(t));

                        _that.container.find('#tables > div').click(
                            function(){
                                $('#tables > div').removeClass('active');
                                $(this).closest('div').addClass('active');
                                $('#tableborder #table').show();
                                _that.loadTable($(this).attr('guid'));
                            }
                        );
                        _that.container.find('#tables > div').first().click();
                    }
                );

                setInterval(function(){
                    $.post(
                        '/table/getDBConnect',
                        function(data){
                            if( data == 'fail' ){
                                $('#dbstatus').css('color', 'red');
                            }else{
                                $('#dbstatus').css('color', 'green');
                            }
                        }
                    )
                }, 10000);

            }

            this.loadTable = function (guid) {
                url = '/table/getTableDefine/table';
                dom = _that.container.find('#right');
                
                $.post(
                    url,
                    {guid: guid},
                    function(data){
                        dom.find('#tablename').text(data.tableName).parent().attr('guid', data.guid);
                        dom.find('#inputborder').attr('guid', data.guid);
                        _that.initInputBorder(data);
                        _that.initRecordList(guid);
                    }
                );
            }

            this.initRecordList = function (guid) {
                this.container.find('#list div.table').empty();
                new rc(this.container.find('#list'), guid, this.ec).init();
            }


            this.initInputBorder = function (data) {
                this.container.find('#inputborder').empty();
                new inputborder(this.container.find('#inputborder'), this.ec).init(data); 
            }

            this.getGuid = function(){
                return 'xyxxyxy'.replace(/[xy]/g,function(c){
                   var r = Math.random()*16|0,
                   v = c == 'x' ? r :(r&0x3|0x8);
                   return v.toString(16);
                });
            };

            this.exports = {
                "getGuid": function(){
                    return _that.getGuid();
                },
                "insert": function(guid){
                    new rc(_that.container.find('#list'), guid, _that.ec).init();
                },
                "editRecord": function(data){
                    _that.ec.fire(
                        'Index',
                        'updateBoard',
                        data
                    );
                }
            }
        };

        return Index;
    }
)