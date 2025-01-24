define(
	function(){
       var DataVerifier = {};

       DataVerifier.qj2bj = function(str) {
            var tmp = "";
            for (var i = 0; i < str.length; i++) {
                if (str.charCodeAt(i) >= 65281 && str.charCodeAt(i) <= 65374) {// 如果位于全角！到全角～区间内
                    tmp += String.fromCharCode(str.charCodeAt(i) - 65248)
                } else if (str.charCodeAt(i) == 12288) {// 全角空格的值，它没有遵从与ASCII的相对偏移，必须单独处理
                    tmp += ' ';
                } else {// 不处理全角空格，全角！到全角～区间外的字符
                    tmp += str[i];
                }
            }
            return tmp;
        };


        DataVerifier.verifyEmail = function(email) {
            var myreg = /^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
            return myreg.test(email.trim());
        };	

        DataVerifier.isInt = function(value){
            return /^(\-)?[0-9]+$/.test(value);
        }

        DataVerifier.isMobile = function(value){
            return /^1[3456789]\d{9}$/.test(value);
        }
        
        DataVerifier.isDouble = function(value){
            return /^-?\d+(\.\d+)?$/.test(value);
        }

        DataVerifier.isObject = function( obj ){
            return Object.prototype.toString.call(obj) === '[object Object]';
        }

        DataVerifier.isAmount = function(value) {
            const regex = /^-?\d+(\.\d+)?$/;
            if( !regex.test(value) && parseFloat(value) <= 0 ){
                return false;
            }
        
            // 检查是否包含小数点，并且小数点后最多两位
            const amountString = value.toString();
            const decimalIndex = amountString.indexOf('.');
            if (decimalIndex === -1) {
                // 没有小数点，直接返回true
                return true;
            } else {
                // 检查小数点后是否有两位数字
                const decimalPart = amountString.substring(decimalIndex + 1);
                return decimalPart.length <= 2;
            }
        }


        DataVerifier.verifyDay = function( value ){
            return /^\d{4}(\-|\/|\.)\d{1,2}\1\d{1,2}$/.test(value);
        }

        DataVerifier.verifyYear = function( value ){
            return /^\d{4}$/.test(value);
        }

        DataVerifier.getGuid = function(){
            return 'xyxxyxy'.replace(/[xy]/g,function(c){
                var r = Math.random()*16|0,
                v = c == 'x' ? r :(r&0x3|0x8);
                return v.toString(16);
            });
        }

        DataVerifier.similar = function(s, t, f) {
            if (!s || !t) {
              return 0
            }
            if(s === t){
              return 100;
            }
            var l = s.length > t.length ? s.length : t.length
            var n = s.length
            var m = t.length
            var d = []
            f = f || 2
            var min = function (a, b, c) {
              return a < b ? (a < c ? a : c) : (b < c ? b : c)
            }
            var i, j, si, tj, cost
            if (n === 0) return m
            if (m === 0) return n
            for (i = 0; i <= n; i++) {
              d[i] = []
              d[i][0] = i
            }
            for (j = 0; j <= m; j++) {
              d[0][j] = j
            }
            for (i = 1; i <= n; i++) {
              si = s.charAt(i - 1)
              for (j = 1; j <= m; j++) {
                tj = t.charAt(j - 1)
                if (si === tj) {
                  cost = 0
                } else {
                  cost = 1
                }
                d[i][j] = min(d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + cost)
              }
            }
            let res = (1 - d[n][m] / l) *100
            return res.toFixed(f)
        }
        
        DataVerifier.verify = function( type ){
            var obj = {};
            switch( type ){
                case 'email': 
                    obj.exec = this.verifyEmail;
                    obj.metion = this.verifyFailMsg.email;
                    break;
                case 'int':
                    obj.exec = this.isInt;
                    obj.metion = this.verifyFailMsg.int;
                    break;
                case 'double':
                    obj.exec = this.isDouble;
                    obj.metion = this.verifyFailMsg.double;
                    break;
                case 'date':
                    obj.exec = this.isDouble;
                    obj.metion = this.verifyFailMsg.date;
                    break;
                case 'year':
                    obj.exec = this.verifyYear;
                    obj.metion = this.verifyFailMsg.year;
                    break;
                default:
                    obj = null;
            }
            return obj;
        }

        DataVerifier.verifyFailMsg = {
            'email' : '电子邮件的格式不正确，请确认后再输入! ',
            'nonull' : '必填项，请输入信息!',
            'int' : '请输入整数值！',
            'double': '请输入浮点数！',
            'date' : '请正确输入日期，日期格式为年/月/日，以/、-、.分隔!',
            'year': '年份应输入四位整数!'
        }
    
       return DataVerifier;
})