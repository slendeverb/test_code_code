define(
    ['template',  'dboper'],
    function(template,  dboper){
        function  Admin(container){
            this.container = container;

            var _that = this;
            this.init = function(){
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
                                _that.loadTableDefine($(this).closest('div').attr('guid'), 'true');
                                $('#tableborder #table').show();
                            }
                        );

                        _that.container.find('#tables > div').first().click();
                    }
                );

                this.container.find('#deleteTable').click(  function(){
                    var guid = _that.container.find('#tableborder #table').attr('guid');
                    var url = '/table/delTable';
                    if( confirm('确定删除该表吗,将会从库中将该表内容全部删除？') ){
                        new dboper(_that.getGuid(), function(data){
                            alert('表删除成功!');
                            window.location.reload();
                        }).send(url, {guid: guid});
                    }
                });

                this.container.find('.tabs .tab').click(
                    function(){
                        var target = $(this).attr('tag');
                        $('.tabs .tab').removeClass('active');
                        $(this).addClass('active');
                        $('.content>div').hide();
                        $('#'+target).show();
                    }
                );

                this.container.find('#new #addField').click(
                    function(){
                        var t = $('#newField').html();
                        $('#metion').remove();
                        $('#fields').append(t);
                        _that.bindFieldEvent();
                    }
                );

                this.container.find('#tableborder #addField').click(
                    function(){
                        var fname = $('#tableborder #fieldname').val();
                        var ftype = $('#tableborder #fieldtype').val();
                        var isnull = $('this').parent().find('[null]').hasClass('checked') ? 1 : 0;
                        var ledgy = $('this').parent().find('[ledgy]').hasClass('checked') ? 1 : 0;
                        if( !!fname && !!ftype){
                            if(confirm('确定添加字段吗？')){
                                var url = '/table/addTableField';
                                var tableGuid = $('#tableborder #table').attr('guid');
                                new dboper(_that.getGuid(), function(data){
                                    alert('字段添加成功!');
                                }).send(
                                    url, {
                                        tid: tableGuid,
                                        fname: fname,
                                        ftype: ftype,
                                        isnull: isnull,
                                        ledgy: ledgy
                                    }
                                );
                            }
                        }else{
                            alert('字段名和字段类型不能为空');
                        }
                    }
                );

                this.container.find('#modname').click(
                    function(){
                        var name = $('#tableborder #tablename').val();
                        console.log(name); 
                        if( !!name ){
                            if(confirm('确定修改表名吗？')){
                           
                                $.post(
                                    '/table/modName',
                                    {guid: $('#tableborder #table').attr('guid'), name: $('#tableborder #tablename').val()},
                                    function(data){
                                        alert('修改成功!'); 
                                    }
                                );
                            }
                        }else{
                            alert('表名不能为空');
                        }
                        
                    }
                );

                this.container.find('.delField').click(
                    function(){
                        $(this).parent().remove();
                    }
                );

                this.container.find('#saveCache').click(
                    function(){
                        
                        var url = '/table/saveCache';
                        $.post(
                            url,
                            {jsonStr: JSON.stringify(_that.getTableDefine())},
                            function(data){
                                alert('暂存成功!');
                                window.location.reload();
                            }
                        );
                    }
                );

                this.container.find('#deleteCache').click(
                    function(){
                        if( confirm('确定删除缓存的表单定义吗？') ){
                            var url = '/table/delCache';
                            $.post(
                                url,
                                {guid: $('#new').attr('guid')},
                                function(data){
                                    window.location.reload();
                                }
                            );
                        }
                    }
                );

                this.container.find('#importDB').click(
                    function(){
                        if( confirm('确定导入数据库吗？') ){
                            if( _that.check()){
                                var url = '/table/import';
                                new dboper(_that.getGuid(), function(data){
                                    alert('导入成功!');
                                    window.location.reload();
                                }).send(url, _that.getTableDefine());
                            }
                        }
                    }
                );
                this.container.find('#exit').click(
                    function(){
                        $.post(
                            '/exit',
                            function(data){
                                window.location.href = '/';
                            }
                        )
                    }
                )

                _that.getDefineList();
            } 

            this.getGuid = function(){
                return 'xyxxyxy'.replace(/[xy]/g,function(c){
                   var r = Math.random()*16|0,
                   v = c == 'x' ? r :(r&0x3|0x8);
                   return v.toString(16);
                });
            };

            this.bindFieldEvent = function(){
                _that.container.find('#new .delField').unbind().click(   
                    function(){
                        $(this).closest('.field').remove();
                    }
                );

                _that.container.find('#tableborder .delField').unbind().click(   
                    function(){
                        if(confirm('确定删除该字段吗,将会从库中将该字段内容全部删除？')){
                            var url = '/table/delTableField';
                            var fieldGuid = $(this).closest('.field').attr('guid');
                            var tableGuid = _that.container.find('#tableborder #table').attr('guid');
                            console.log(fieldGuid, tableGuid);
                            new dboper(_that.getGuid(), function(data){
                                alert('字段删除成功!');
                            }).send(
                                url, {
                                    fid: fieldGuid,
                                    tid: tableGuid
                                }
                            );
                        }
                    }
                );

                _that.container.find('#tableborder .updateField').unbind().click(   
                    function(){
                        if(confirm('确定更新该字段吗,将会影响到库中将该字段的内容？')){
                            var url = '/table/updateTableField';
                            var fieldGuid = $(this).closest('.field').attr('guid');
                            var tableGuid = _that.container.find('#tableborder #table').attr('guid');
                            var fname = $(this).closest('.field').find('input').val();
                            var ftype = $(this).closest('.field').find('select').val();
                            var isnull = $(this).closest('.field').find('[null]').hasClass('checked') ? 1 : 0;
                            var ledgy = $(this).closest('.field').find('[ledgy]').hasClass('checked') ? 1 : 0;

                            console.log(fieldGuid, tableGuid, fname, ftype, isnull, ledgy);
                            new dboper(_that.getGuid(), function(data){
                                alert('字段修改成功!');
                            }).send(
                                url, {
                                    fid: fieldGuid,
                                    tid: tableGuid,
                                    fname: fname,
                                    ftype: ftype,
                                    isnull: isnull,
                                    ledgy: ledgy
                                }
                            );
                        }
                    }
                );

                _that.container.find('span.nocheck').unbind().click(   
                    function(){
                        if($(this).hasClass('checked')){
                            $(this).removeClass('checked');
                        }else{
                            $(this).addClass('checked');
                        }
                    }
                );
            }

            this.check = function(){
                var data = this.getTableDefine();
                console.log(data);
                if( !data.tableName ){
                    alert('表名不能为空');
                    return false;
                }
                if( !data.fields || data.fields.length == 0 ){
                    alert('字段不能为空');
                    return false;
                }
                for( var i=0; i<data.fields.length; i++ ){
                    if( !data.fields[i].name ){
                        alert('字段名不能为空');
                        return false;
                    }
                    if( !data.fields[i].type ){
                        alert('字段类型不能为空');
                        return false;
                    }
                }
                return true;
            }

            this.getDefineList = function(){
                $.post(
                    '/table/getCache',
                    function(data){
                        var defineTpl = '{{each list as data}}<div class="form-group" style="width: 100%;" guid="{{data.guid}}"><input type="submit" value="{{data.tableName}}" id="loginBut"/></div>{{/each}}';
                        var t = {}; t.list = data; 
                        var html = template.compile(defineTpl)(t);
                        $('#tablecache').append(html);
                        $('#tablecache > div').click(
                            function(){
                                $('#tablecache > div').removeClass('active');
                                $(this).closest('div').addClass('active');
                                _that.loadTableDefine($(this).closest('div').attr('guid'));
                            }
                        );
                    }
                )
            };

            this.updateField = '<div class="updateField" style="background-color: #ccc;border-radius: 2px; color: #fff; cursor: pointer;display: inline-block; width: 28px;"><i class="fa fa-cog" style="cursor: pointer;"></i></div>';

            this.loadTableDefine = function( guid, isTable ){
                if( !!guid ){
                    var url = '';
                    var dom = null;
                    if( !!isTable ){
                        url = '/table/getTableDefine/table';
                        dom = _that.container.find('#tableborder #table');
                    }else{
                        url = '/table/getTableDefine/cache';
                        dom = _that.container.find('#new');
                    }
                    $.post(
                        url,
                        {guid: guid},
                        function(data){
                            dom.find('#tablename').val(data.tableName);
                            dom.attr('guid', guid);
                            dom.find('#fields').empty();
                            for( var i=0; i<data.fields.length; i++ ){
                                var field = data.fields[i];
                                var t = $('#newField').html();
                                if( !!isTable){
                                    t = $(t);
                                    $(_that.updateField).insertAfter(t.find('.delField'));
                                }
                                
                                dom.find('#fields').append(t);
                                console.log(field.guid);
                                dom.find('#fields .field').last().val(field.name).parent().attr('guid', field.guid);
                                dom.find('#fields .fieldtype').last().val(field.type);

                                if( field.null == 1 ){
                                    dom.find('#fields [null]').last().addClass('checked');
                                }else{
                                    dom.find('#fields [null]').last().removeClass('checked');
                                }

                                if( field.ledgy == 1 ){
                                    dom.find('#fields [ledgy]').last().addClass('checked');
                                }else{
                                    dom.find('#fields [ledgy]').last().removeClass('checked');
                                }
                               
                            }
                            _that.bindFieldEvent();

                        }
                    );
                }else{
                    var metion = '<div id="metion" style="height: 48px; text-align: center; line-height: 48px; color: #ccc; font-style: italic ;">请点击“新增字段”按钮添加字段 </div>';
                    $('#tablename').val('');
                    $('#new').attr('guid', '');
                    $('#fields').empty().append(metion);
                }
            }

            this.getTableDefine = function(  ){
                var data = {};
                data.tableName = this.container.find('#tablename').val();
                data.guid = this.container.find('#new').attr('guid');
                data.fields = [];
                this.container.find('#new #fields>div').each(
                    function(){
                        
                        var field = {};
                        field.name = $(this).find('.field').val();
                        field.type = $(this).find('.fieldtype').val();
                        field.null = $(this).find('[null]').hasClass('checked') ? 1 : 0;
                        field.ledgy = $(this).find('[ledgy]').hasClass('checked') ? 1 : 0;
                        data.fields.push(field);
                    }
                );

                return data;
            }
            
            
        }
        return Admin;
    }
)