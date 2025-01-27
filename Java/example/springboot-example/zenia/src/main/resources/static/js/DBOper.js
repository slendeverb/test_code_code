define(
    [],
    function () {
        function DBOper(taskid, callback) {
            this.callback = callback;
            this.taskid = taskid;

            this.tryCount = 10; //尝试次数

            var _that = this;

            this.send = function (url, data) {
                $.post(
                    url,
                    {taskid: taskid, jsonStr: JSON.stringify(data)},
                    function (result) {
                        setTimeout(function(){
                            _that.getRst(result);
                        }, 100);
                    }
                );
            }

            this.getRst = function (data ) {
                $.post(
                    '/table/getRst',
                    {taskid: _that.taskid},
                    function (result) {
                        if( !!result ){
                            _that.callback(result, data);
                        }else{
                            if(--_that.tryCount>0){
                                setTimeout(function(){
                                    _that.getRst();
                                }, 100);
                            }else{
                                alert('请求超时');
                            }
                        }
                    }
                );
            }
        }
        return DBOper;
    }
);