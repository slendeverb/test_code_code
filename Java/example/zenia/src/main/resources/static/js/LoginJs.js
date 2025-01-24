define(
    [],
    function(){
        function Login(container){
            this.container = container;
            this.init = function(){
                this.container.find("#loginBut").click(
                    function(){
                        var username = $("#username").val();
                        var password = $("#password").val();
                        if( !!username && !!password ){
                            $.ajax({
                                url: '/user/login',
                                type: 'post',
                                data: {un: username, ps: password},
                                success: function(data){
                                   
                                    if( data == 'true'  ){
                                        window.location.href = '/admin';
                                    }else{
                                        alert('用户名或密码错误，请重新输入');
                                    }
                                }
                            })
                        }else{
                            alert('请填写用户名和密码');
                        }
                    }
                );
                
            }
        }
        return Login;
    }
)