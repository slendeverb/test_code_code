define(
    ['inputwidgets', 'template', 'dboper', 'datepicker', 'dataverifier'],
    function (inputwidgets, template, dboper,datepicker, dv) {
        function Complete(dom){
            this.dom = dom;
            this.datas = null;
            
            var _that = this;
            this.completeTpl = '<div class="autocomplete">{{each list as data}}<div class="item">{{data}}</div>{{/each}}</div>';
            this.listRender = template.compile(this.completeTpl);
            this.init = function(){
                new dboper(
                    dom.attr('tableid') + "_" + dom.attr('fieldid'),
                    _that.initComplete
                ).send('/autocomplete', {tid:dom.attr('tableid'), fid:dom.attr('fieldid')});
            };

            this.initComplete = function(data){
               
                _that.datas = data.rst;
                _that.dom.find('input').keyup(
                    function(){
                        _that.update($(this).val());
                    }
                ).focus(
                    function(){
                        _that.dom.find('.autocomplete').css('width', _that.dom.width() + 'px').show();
                    }
                );
                //_that.dom.find('input').keyup().blur();
            }

            this.update = function(key){
                var tmp = [];
                if( !!key ) {
                    for(var i=0; i<_that.datas.length; i++){
                        for( var k in _that.datas[i]){
                            if( _that.datas[i][k].indexOf(key) != -1){
                                tmp.push(_that.datas[i][k]);
                            }
                        }
                    }
                }else{
                    for(var i=0; i<_that.datas.length; i++){
                        for( var k in _that.datas[i]){
                            tmp.push(_that.datas[i][k]);
                        }
                    }
                }
                
                
                var data = {}; data.list = tmp;
                //console.log(_that.listRender(data))
                _that.dom.find('.autocomplete').empty().end().append(_that.listRender(data));
                _that.dom.find('.autocomplete').css('width', _that.dom.width() + 'px').show();
                //console.log(_that.listRender(data));
                _that.dom.find('.item').click(
                    function(e){
                        console.log($(this).text());
                        _that.dom.find('input').val($(this).text());
                        _that.dom.find('.autocomplete').hide();
                        e.stopPropagation();
                    }
                )
            }
        }

        function InputBorder(dom, ec) {
            this.dom = dom;
            this.ec = ec;
            this.name = "InputBorder";
            this.ec.addHandler(this);
            
            var _that = this;
            
            this.init = function (data) {
                dom.empty();
                data.fields = data.fields.sort((a,b)=> b.type - a.type);
                //console.log(data.fields);
                for(var i=0; i<data.fields.length; i++){
                    var jdom = this.getDom(data.fields[i], data.guid);
                    dom.append(jdom);
                }

                this.initComplete(dom);
                new datepicker(dom).init(function(){

                });
                dom.append('<input type="submit" value="提交" style="background-color:green;border:0px;" id="submit">')


                dom.find('#submit').click(function(){
                    if( !!_that.dom.attr('rid') ){
                        _that.updateRecord();
                    }else
                        _that.insert();
                })
            
            }

            this.updateRecord = function(){
                var data = _that.getData();
                var rid = _that.dom.attr('rid');
                var guid = _that.dom.attr('guid');
                if( data == null){
                    alert('请检查输入数据是否正确，及必填项是否漏填！');
                }else{
                    var rst = _that.ec.fire(
                        'InputBorder',
                        'getGuid',
                        {}
                    );
                    
                    new dboper(
                        rst[0].rst, function(){
                            alert('修改成功！');
                        }
                    ).send('/update/recorde/' + guid + "/" + rid, data);
                }
            }


            this.insert = function(  ){
                var data = _that.getData();
                console.log(data);
                if( data == null){
                    alert('请检查输入数据是否正确，及必填项是否漏填！');
                }else{
                    var rst = _that.ec.fire(
                        'InputBorder',
                        'getGuid',
                        {}
                    );
                    new dboper(
                        rst[0].rst, function(){
                             _that.clear();
                            _that.ec.fire(
                                'InputBorder',
                                'insert',
                                _that.dom.attr('guid')
                            )
                        }
                    ).send('/insert/' + _that.dom.attr('guid'), data);
                }
            }
            this.clear = function(){
                this.dom.attr('rid', '');
                this.dom.find('div[type]').removeClass('error');
                this.dom.find('input:not("#submit")').val('');
                this.dom.find('input[type="radio"]').prop('checked', false);
                this.dom.find('input[true]').val('1');
                this.dom.find('input[false]').val('0');
                this.dom.find('textarea').val('');
                this.dom.find('.datePicker').attr('val','').text('');
                this.dom.find('#submit').val('提交');
            }

            this.initComplete = function( dom ){
                var inputs = dom.find('>div');
                for(var i=0; i<inputs.length; i++){
                    var input = inputs.eq(i);
                    if( !!input.attr('url') ) { 
                        new Complete(input).init();
                    }
                }
            }


            this.getDom = function( field, guid ){
                if( field.type == '7') return null; //不需要输入的，自动添加时间戳
                var dom = $('<div type='+ parseInt(field.type)+' guid='+field.guid+'>');
                
                var t = '';
                if( field.type == '6'){
                    t = '<label>'+field.name+'</label><div style="border:1px solid #aaa; border-radius:2px;text-align:center;line-height: 24px;background-color:#fff;">是<input type="radio" name="'+field.guid+'" value="1" true /> 否<input type="radio" name="'+field.guid+'" value="0" false/></div>'
                }else if(field.type == '0'){
                    t = '<label>'+field.name+'</label><textarea ></textarea>'
                }else if(field.type == '5'){
                    t = '<label>'+field.name+'</label><div class="datePicker" id="'+ field.guid +'"></div>'
                }else{
                    t = '<label>'+field.name+'</label><input type="text" value=""  />'
                }
                dom.append(t);
                if( field.null == 0){
                    dom.addClass('required');
                    dom.find('label').addClass('required');
                }
                if( field.ledgy == 1){
                    dom.attr('tableid',  guid).attr('fieldid',  field.guid).attr('url', '/autocomplete');
                }
                return dom;
            }

            this.getData = function(){
                var data = {};
                this.dom.find('div[type]').removeClass('error');
                
                this.dom.find('div[type]').each(
                    function(){
                        var type = $(this).attr('type');
                        var guid = $(this).attr('guid');
                        var flag = false;
                        var val = '';
                        if( type == '6'){
                            val = $(this).find('input:checked').val();
                            console.log(val);
                        }else if(type == '0'){
                            val = $(this).find('textarea').val();
                        }else if(type == '5'){
                            val = $(this).find('div').attr('val');
                        }else{
                            val = $(this).find('input').val();
                        }

                        if( $(this).hasClass('required') && !val){
                            flag = true;
                        }

                        if( type == '4' && !dv.isAmount(val)){
                            console.log(dv.isAmount(val));
                            flag = true;;
                        }else if(type == '3' && !dv.isDouble(val)){
                            flag = true;;

                        }else if(type == '2' && !dv.isInt(val)){
                            flag = true;;
                        }

                        if( flag ){
                            $(this).addClass('error');
                        }else{
                            data[guid] = val;
                        }
                    }
                );
                if( this.dom.find('.error').length > 0){
                    return null;
                }else 
                    return data;
            }


            this.initData = function( data ){
                if(!$('#edit').parent().hasClass('active')){
                    $('#edit').click();
                };

                _that.dom.attr('rid', data.id);
                _that.dom.find('.no').remove().end().append('<div style="position: absolute; top: 2px; right: 8px; " class="no">NO:<span style="color:red">'+ data.id +'</span></div>')
                for(var key in data){
                    var dom = _that.dom.find('div[guid="'+key+'"]');
                    if( dom.attr('type') == '6'){
                        if(data[key] == '1'){
                            dom.find('input[true]').click();
                        }else{
                            dom.find('input[false]').click();
                        }
                       
                    }else if(dom.attr('type') == '5'){
                        dom.find('div').attr('val', data[key]).text(data[key]);
                    }else if(dom.attr('type') == '0'){
                        dom.find('textarea').val(data[key]);
                    }else{
                        dom.find('input').val(data[key]);
                    }
                }
                
                _that.dom.find('#submit').val('修改');
            }

            this.exports = {
                "updateBoard": function( data ){
                    var r = data.rst[0];
                    _that.initData(r);
                },
                "clear": function(){
                    _that.clear();
                }

            }
            

            this.dataTypes = [
                'LONG_TEXT',
                'TEXT',
                'INTEGER',
                'DOUBLE',
                'PRICE',
                'DATETIME',
                'BOOLEAN',
                'TIMESTAMP'
            ]
            
        }
        return InputBorder;
    }
)