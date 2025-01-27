define(
    ['layui'],
    function(layui){
        function DatePicker(container){
            this.name = "DatePicker";
            this.container = container;
            var _that = this;

            this.init = function( callback ){  
                this.container.find('.datePicker').each(
                    function(){
                        var id = $(this).attr('id');
                        var _that = $(this);
                        //时间日期插件：laydate
                        layui.laydate.render({
                            elem: '#'+id,
                            lang: 'cn',
                            format: 'yyyy-MM-dd', //日期格式
                            ready: function(date){
                                $('.laydate-prev-y').empty().addClass('preyear');
                                $('.laydate-prev-m').empty().addClass('premonth');
                                $('.laydate-next-y').empty().addClass('nextyear');
                                $('.laydate-next-m').empty().addClass('nextmonth');
                            },
                            done: function(value, date, endDate){
                                _that.attr('val',value);
                                callback(value, date, endDate);
                            }
                        });
                    }
                )
                return this;
            };
        }

        return DatePicker;
    }
);