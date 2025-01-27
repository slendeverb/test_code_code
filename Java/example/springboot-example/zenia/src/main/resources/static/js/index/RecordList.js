define(
    ['template', 'dboper', 'pop', 'uploader', 'downloader'],
    function( template, dboper, pop, uploader,downloader ){
        function RecordList( dom, guid, ec ){
            this.name = "RecordList";
            this.dom = dom;
            this.guid = guid;
            this.ec = ec;
            this.ec.addHandler( this );
            this.popup = new pop(this.ec).init();

            var _that = this;
            this.init = function(  ){
                this.dom.find('.table').empty();
                new dboper(
                    '/getDefaultView/'+this.guid,
                    this.initRecordList
                ).send('/table/getDefaultView/' + this.guid, {});
            }

            this.tableHead = '<div class="tablehead"><div class="cell" guid="id">编号</div>{{each list as data}}<div class="cell" guid="{{data.guid}}">{{data.name}}</div>{{/each}}</div>';

            this.tableBody = '<div class="tablebody">{{ each data as row }}<div class="row" id={{row.id}}><div class="cell" guid="{{row.id}}">{{row.id}}</div>{{each row.row as d}}<div class="cell" guid="{{d.guid}}">{{d.value}}</div>{{/each}}</div>{{/each}}</div>';

            this.rowContr = '<div class="contr"><span><i class="fa fa-edit" oper="edit"></i></span><span><i class="fa fa-cloud-upload" oper="attch"></i></span><span><i class="fa fa-file-o" oper="attchlist"></i></span><span><i class="fa fa-trash" oper="del"></i></span></div>'; 
            this.initRecordList = function( data, viewDef ){
                var fields = viewDef;

                var list_fields = []; 
                for(var i=0; i<fields.length; i++){
                    list_fields.push( { name: fields[i].name, guid: fields[i].guid } );
                    if( i == 0){
                        list_fields.push( { name: fields[i].name, guid: fields[i].guid } );
                    }
                }

                var t = {}; t.list = list_fields;
                _that.dom.find('.table').append(template.compile(_that.tableHead)(t)); // 表头

                var rows = [];
                for(var i=0; i<data.rst.length; i++){
                    var o = data.rst[i];
                    var tmp = {}; tmp.row = [];
                    for( var j=0; j<list_fields.length; j++){
                        tmp.row.push( { guid: list_fields[j].guid, value: o[list_fields[j].guid] } );
                    }
                    tmp.id =  o['id'];
                    rows.push(tmp);
                }
                t = {}; t.data = rows;
                //console.log(t);
                _that.dom.find('.table').append(template.compile(_that.tableBody)(t)); 
                _that.dom.find('.row').mouseover(
                    function(){
                        $(this).find('.cell').css('background-color', 'lightyellow');
                    }
                ).mouseout(
                    function(){
                        $(this).find('.cell').css('background-color', '#fff');
                    }
                ).append(_that.rowContr);
                
                _that.dom.find('.contr i').click(
                    function(){
                        var oper = $(this).attr('oper');
                        var rid = $(this).closest('.row').attr('id');
                        switch( oper ){
                            case 'edit':
                                _that.edit(rid);
                                break;
                            case 'del':
                                _that.del(rid);
                                break;
                            case 'attch':
                                _that.attach(rid);
                                break;
                            case 'attchlist':
                                _that.attachListShow(rid);
                                break;
                        }
                    }
                );
            }

            this.attachListShow = function( rid ){
               
                var rst = _that.ec.fire(
                    'RecordList',
                    'getGuid',
                    {  }
                );
                new dboper(
                    rst[0].rst,  
                    function( data ){
                        _that.popup.pop('attachList', 688, function( dom ){
                            dom.attr('rid', rid);
                            _that.attachListInit(dom, data, rid );
                        });
                    }
                ).send('/table/getAttachment/' + _that.guid + '/' + rid, {  });
            }

            this.attachListInit = function(dom, data, rid ){
                console.log(data);
                var itemTpl = '{{each rst as data }} <div class="attachrow" guid={{data.attach_guid}} id={{data.id}}><div class="listcontr"><span><i class="fa fa-trash" oper="del"></i></span><span><i class="fa fa-download" oper="download"></i></span></div><div class="file">{{data.attach_file_name}}</div></div> {{/each}}';
                var render = template.compile(itemTpl);
                var list = render( data );
                dom.find('#list').empty().append( list );
                dom.find('.listcontr i').click(_that.attachListOper);
            }

            this.attachListOper = function(){
                var oper = $(this).attr('class');
                var id = $(this).closest('.attachrow').attr('id');
                var rid = $(this).closest('.attachrow').attr('guid');
                var fname = $(this).closest('.attachrow').find('.file').text();
                switch( oper ){
                    case 'fa fa-trash':
                        _that.attachListDel($(this).closest('.attachrow'), rid, id);
                        break;
                    case 'fa fa-download':
                        _that.attachListDownload(rid, fname);
                        break;
                }
            }

            this.attachListDel = function(dom, rid, id ){
                if( !confirm('确定要删除该附件吗？')) return;
                dom.remove();
                var rst = _that.ec.fire(
                    'RecordList',
                    'getGuid',
                    {  }
                );
                new dboper(
                    rst[0].rst,  
                    function(){
                        //_that.attachListShow( rid );
                    }
                ).send('/table/delAttachment/' + rid + "/" + id, {  });
            }
            

            this.attachListDownload = function( rid, fname ){
                new downloader().down('/table/download/'+rid, fname);
            }

            this.attach = function( rid ){
                  
                _that.popup.pop('attach', 688, function( dom ){
                    dom.attr('rid', rid);
                    uploader.initAll(dom, _that.ec);
                });
            }

            this.edit = function( rid ){
                var rst = _that.ec.fire(
                    'RecordList',
                    'getGuid',
                    {  }
                );
                new dboper(
                    rst[0].rst,  
                    function( data ){
                        _that.ec.fire(
                            'RecordList',
                            'editRecord',
                            data
                        );
                    }
                ).send(
                    '/table/getRecode/' + _that.guid + '/' + rid,
                    {  }
                );
            }

            this.del = function( rid ){
                if( confirm('确定要删除该记录吗？')){
                    var rst = _that.ec.fire(
                        'RecordList',
                        'getGuid',
                        {  }
                    );
                    new dboper(
                        rst[0].rst,  
                        function(){
                            _that.init();
                        }
                    ).send('/table/delRecord/' + _that.guid + '/' + rid, {  });
                }
            }

            this.attachList = '<div class="attach" guid="{{innerId}}" fname="{{originName}}"><div class="trash"><i class="fa fa-trash"></i></div><div class="name">{{ originName }}</div></div>';
            this.attachRender = template.compile(this.attachList);
            this.uploadAttach = function( args ){
               var list = this.attachRender(args);
               $('#attachment').append( list );
               $('#attachment .note').text('');

               $('#attachment .trash').click(
                    function(){
                        $(this).closest('.attach').remove();
                    }
               )
            }

            this.bindAttach = function( rid ){
                var list = $('#attachment .attach');
                var ids = [];
                for(var i=0; i<list.length; i++){
                    var data = {};
                    data.innerId = $(list[i]).attr('guid');
                    data.originName = $(list[i]).attr('fname');
                    ids.push( data );
                }

                var rst = _that.ec.fire(
                    'RecordList',
                    'getGuid',
                    {  }
                ); 
                new dboper(
                    rst[0].rst,
                    function(){
                        _that.popup.close();
                    }
                ).send('/table/saveAttachment/'+_that.guid+ "/" + rid, { ids: ids });
            }

            this.exports = {
                "popbutton": function( args ){
                    if( args.bid == 'confirm'){
                        _that.bindAttach( args.dom.attr('rid') );
                    }else if(args.bid == 'cancel'){
                        _that.popup.close();
                    }
                },
                "uploaded": function( args ){
                    _that.uploadAttach(args);
                }
            }

        }
        return RecordList;
    }
)