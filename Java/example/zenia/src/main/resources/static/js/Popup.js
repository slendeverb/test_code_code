define(
    ['layui'],
    function(layer){
        function Popup(ec){
            this.name = "POPUP";
            this.ec = ec;
            this.ec.addHandler( this );

            var _that = this;
            this.init = function(){
                var layer = layui.layer;
                layer.config({
                    path: '/js/layui/lay/modules'
                });

                this.layer = layer;
                return this;
            };

            this.confirm = function(title, msg, size, execFun, domFun){
                var url = '/pop/confirm/'+ title + "/" + encodeURI(msg);
                _that.popup(url, "confirm", size, function( dom ){
                    if(!!domFun) domFun(dom);
                    dom.find('#cancel').click(
                        function(){
                            _that.close();
                        }
                    );

                    dom.find('#confirm.popbut').click(
                        function(){
                            execFun(dom);
                            _that.close();
                        }
                    );

                }, null );
            }

            this.msgbox = function(type, msg, size){
                var url = '/pop/msg/'+ type + '/' + msg;
                _that.popup(url, "msgbox", size, function( dom ){
                    dom.find('#msgbox-confirm').click(
                        function(){
                            _that.close();
                        }
                    )
                }, null );
            }

            this.pop = function(id, size, initFun, mask){
                var url = '/pop/'+id;
                _that.popup(url, id, size, initFun, mask );
            }


            this.popup = function(url, id, size, initFun, mask){
                $.post(
                    url,   //'/pop/'+id,
                    function(rst){
                        var dom = $(rst);
                        var title = dom.find('[title]').attr("title");
                        var font  = dom.find('[font]').attr("font");
                        dom.find('#title span').text(title);
                        dom.find('#title i').addClass(font);

                        var domId = id;
                        var callback = function(dom, index){
                            var buttons = $(dom).find('.popbut');
                            buttons.each(
                                function(  ){
                                    $(this).click( 
                                        function(){
                                            _that.ec.fire(
                                                _that.name,
                                                'popbutton',
                                                {
                                                    dom: domId,
                                                    bid: $(this).attr('id'), 
                                                    layer: _that,
                                                    dom: dom
                                                }
                                            )
                                        }
                                        
                                    );
                                }
                            );

                            if(!!initFun) initFun( dom );
                        }

                        var m = !!mask ? mask : [0.3, '#000'];
                        var layIdnex =  _that.layer.open({
                            title: false,
                            closeBtn: 1,
                            offset: '80px',
                            fixed: false,
                            type: 1,
                            content: dom.html(),
                            area: size + 'px',
                            shade: m,
                            success: function(layero, index){
                                callback(layero, index);
                            }
                        });
        
                        _that.layIdnex = layIdnex;
                    }
                )
            }

            this.close = function(){
                this.layer.close(_that.layIdnex);
            }
        }


        return Popup;
    }
)