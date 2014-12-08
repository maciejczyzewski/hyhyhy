/*!                          main.js | © 2014 hyhyhy                        !*/

//= require_self
//= require_tree .
//= require_tree shared

/* =========================================================================
   Configure
   ========================================================================= */

/*!
 * Prism.js master (04.06.2014)
 *
 * Copyright 2014, Lea Verou
 * This content is released under the MIT license
 */

self=typeof window!="undefined"?window:typeof WorkerGlobalScope!="undefined"&&self instanceof WorkerGlobalScope?self:{};var Prism=function(){var e=/\blang(?:uage)?-(?!\*)(\w+)\b/i,t=self.Prism={util:{encode:function(e){return e instanceof n?new n(e.type,t.util.encode(e.content),e.alias):t.util.type(e)==="Array"?e.map(t.util.encode):e.replace(/&/g,"&amp;").replace(/</g,"&lt;").replace(/\u00a0/g," ")},type:function(e){return Object.prototype.toString.call(e).match(/\[object (\w+)\]/)[1]},clone:function(e){var n=t.util.type(e);switch(n){case"Object":var r={};for(var i in e)e.hasOwnProperty(i)&&(r[i]=t.util.clone(e[i]));return r;case"Array":return e.slice()}return e}},languages:{extend:function(e,n){var r=t.util.clone(t.languages[e]);for(var i in n)r[i]=n[i];return r},insertBefore:function(e,n,r,i){i=i||t.languages;var s=i[e];if(arguments.length==2){r=arguments[1];for(var o in r)r.hasOwnProperty(o)&&(s[o]=r[o]);return s}var u={};for(var a in s)if(s.hasOwnProperty(a)){if(a==n)for(var o in r)r.hasOwnProperty(o)&&(u[o]=r[o]);u[a]=s[a]}t.languages.DFS(t.languages,function(t,n){n===i[e]&&t!=e&&(this[t]=u)});return i[e]=u},DFS:function(e,n,r){for(var i in e)if(e.hasOwnProperty(i)){n.call(e,i,e[i],r||i);t.util.type(e[i])==="Object"?t.languages.DFS(e[i],n):t.util.type(e[i])==="Array"&&t.languages.DFS(e[i],n,i)}}},highlightAll:function(e,n){var r=document.querySelectorAll('code[class*="language-"], [class*="language-"] code, code[class*="lang-"], [class*="lang-"] code');for(var i=0,s;s=r[i++];)t.highlightElement(s,e===!0,n)},highlightElement:function(r,i,s){var o,u,a=r;while(a&&!e.test(a.className))a=a.parentNode;if(a){o=(a.className.match(e)||[,""])[1];u=t.languages[o]}if(!u)return;r.className=r.className.replace(e,"").replace(/\s+/g," ")+" language-"+o;a=r.parentNode;/pre/i.test(a.nodeName)&&(a.className=a.className.replace(e,"").replace(/\s+/g," ")+" language-"+o);var f=r.textContent;if(!f)return;var l={element:r,language:o,grammar:u,code:f};t.hooks.run("before-highlight",l);if(i&&self.Worker){var c=new Worker(t.filename);c.onmessage=function(e){l.highlightedCode=n.stringify(JSON.parse(e.data),o);t.hooks.run("before-insert",l);l.element.innerHTML=l.highlightedCode;s&&s.call(l.element);t.hooks.run("after-highlight",l)};c.postMessage(JSON.stringify({language:l.language,code:l.code}))}else{l.highlightedCode=t.highlight(l.code,l.grammar,l.language);t.hooks.run("before-insert",l);l.element.innerHTML=l.highlightedCode;s&&s.call(r);t.hooks.run("after-highlight",l)}},highlight:function(e,r,i){var s=t.tokenize(e,r);return n.stringify(t.util.encode(s),i)},tokenize:function(e,n,r){var i=t.Token,s=[e],o=n.rest;if(o){for(var u in o)n[u]=o[u];delete n.rest}e:for(var u in n){if(!n.hasOwnProperty(u)||!n[u])continue;var a=n[u];a=t.util.type(a)==="Array"?a:[a];for(var f=0;f<a.length;++f){var l=a[f],c=l.inside,h=!!l.lookbehind,p=0,d=l.alias;l=l.pattern||l;for(var v=0;v<s.length;v++){var m=s[v];if(s.length>e.length)break e;if(m instanceof i)continue;l.lastIndex=0;var g=l.exec(m);if(g){h&&(p=g[1].length);var y=g.index-1+p,g=g[0].slice(p),b=g.length,w=y+b,E=m.slice(0,y+1),S=m.slice(w+1),x=[v,1];E&&x.push(E);var T=new i(u,c?t.tokenize(g,c):g,d);x.push(T);S&&x.push(S);Array.prototype.splice.apply(s,x)}}}}return s},hooks:{all:{},add:function(e,n){var r=t.hooks.all;r[e]=r[e]||[];r[e].push(n)},run:function(e,n){var r=t.hooks.all[e];if(!r||!r.length)return;for(var i=0,s;s=r[i++];)s(n)}}},n=t.Token=function(e,t,n){this.type=e;this.content=t;this.alias=n};n.stringify=function(e,r,i){if(typeof e=="string")return e;if(Object.prototype.toString.call(e)=="[object Array]")return e.map(function(t){return n.stringify(t,r,e)}).join("");var s={type:e.type,content:n.stringify(e.content,r,i),tag:"span",classes:["token",e.type],attributes:{},language:r,parent:i};s.type=="comment"&&(s.attributes.spellcheck="true");if(e.alias){var o=t.util.type(e.alias)==="Array"?e.alias:[e.alias];Array.prototype.push.apply(s.classes,o)}t.hooks.run("wrap",s);var u="";for(var a in s.attributes)u+=a+'="'+(s.attributes[a]||"")+'"';return"<"+s.tag+' class="'+s.classes.join(" ")+'" '+u+">"+s.content+"</"+s.tag+">"};if(!self.document){if(!self.addEventListener)return self.Prism;self.addEventListener("message",function(e){var n=JSON.parse(e.data),r=n.language,i=n.code;self.postMessage(JSON.stringify(t.util.encode(t.tokenize(i,t.languages[r]))));self.close()},!1);return self.Prism}var r=document.getElementsByTagName("script");r=r[r.length-1];if(r){t.filename=r.src;document.addEventListener&&!r.hasAttribute("data-manual")&&document.addEventListener("DOMContentLoaded",t.highlightAll)}return self.Prism}();typeof module!="undefined"&&module.exports&&(module.exports=Prism);;
Prism.languages.markup={comment:/<!--[\w\W]*?-->/g,prolog:/<\?.+?\?>/,doctype:/<!DOCTYPE.+?>/,cdata:/<!\[CDATA\[[\w\W]*?]]>/i,tag:{pattern:/<\/?[\w:-]+\s*(?:\s+[\w:-]+(?:=(?:("|')(\\?[\w\W])*?\1|[^\s'">=]+))?\s*)*\/?>/gi,inside:{tag:{pattern:/^<\/?[\w:-]+/i,inside:{punctuation:/^<\/?/,namespace:/^[\w-]+?:/}},"attr-value":{pattern:/=(?:('|")[\w\W]*?(\1)|[^\s>]+)/gi,inside:{punctuation:/=|>|"/g}},punctuation:/\/?>/g,"attr-name":{pattern:/[\w:-]+/g,inside:{namespace:/^[\w-]+?:/}}}},entity:/\&#?[\da-z]{1,8};/gi},Prism.hooks.add("wrap",function(t){"entity"===t.type&&(t.attributes.title=t.content.replace(/&amp;/,"&"))});;
Prism.languages.css={comment:/\/\*[\w\W]*?\*\//g,atrule:{pattern:/@[\w-]+?.*?(;|(?=\s*{))/gi,inside:{punctuation:/[;:]/g}},url:/url\((["']?).*?\1\)/gi,selector:/[^\{\}\s][^\{\};]*(?=\s*\{)/g,property:/(\b|\B)[\w-]+(?=\s*:)/gi,string:/("|')(\\?.)*?\1/g,important:/\B!important\b/gi,punctuation:/[\{\};:]/g,"function":/[-a-z0-9]+(?=\()/gi},Prism.languages.markup&&(Prism.languages.insertBefore("markup","tag",{style:{pattern:/<style[\w\W]*?>[\w\W]*?<\/style>/gi,inside:{tag:{pattern:/<style[\w\W]*?>|<\/style>/gi,inside:Prism.languages.markup.tag.inside},rest:Prism.languages.css},alias:"language-css"}}),Prism.languages.insertBefore("inside","attr-value",{"style-attr":{pattern:/\s*style=("|').+?\1/gi,inside:{"attr-name":{pattern:/^\s*style/gi,inside:Prism.languages.markup.tag.inside},punctuation:/^\s*=\s*['"]|['"]\s*$/,"attr-value":{pattern:/.+/gi,inside:Prism.languages.css}},alias:"language-css"}},Prism.languages.markup.tag));;
Prism.languages.clike={comment:[{pattern:/(^|[^\\])\/\*[\w\W]*?\*\//g,lookbehind:!0},{pattern:/(^|[^\\:])\/\/.*?(\r?\n|$)/g,lookbehind:!0}],string:/("|')(\\?.)*?\1/g,"class-name":{pattern:/((?:(?:class|interface|extends|implements|trait|instanceof|new)\s+)|(?:catch\s+\())[a-z0-9_\.\\]+/gi,lookbehind:!0,inside:{punctuation:/(\.|\\)/}},keyword:/\b(if|else|while|do|for|return|in|instanceof|function|new|try|throw|catch|finally|null|break|continue)\b/g,"boolean":/\b(true|false)\b/g,"function":{pattern:/[a-z0-9_]+\(/gi,inside:{punctuation:/\(/}},number:/\b-?(0x[\dA-Fa-f]+|\d*\.?\d+([Ee]-?\d+)?)\b/g,operator:/[-+]{1,2}|!|<=?|>=?|={1,3}|&{1,2}|\|?\||\?|\*|\/|\~|\^|\%/g,ignore:/&(lt|gt|amp);/gi,punctuation:/[{}[\];(),.:]/g};;
Prism.languages.javascript=Prism.languages.extend("clike",{keyword:/\b(break|case|catch|class|const|continue|debugger|default|delete|do|else|enum|export|extends|false|finally|for|function|get|if|implements|import|in|instanceof|interface|let|new|null|package|private|protected|public|return|set|static|super|switch|this|throw|true|try|typeof|var|void|while|with|yield)\b/g,number:/\b-?(0x[\dA-Fa-f]+|\d*\.?\d+([Ee]-?\d+)?|NaN|-?Infinity)\b/g}),Prism.languages.insertBefore("javascript","keyword",{regex:{pattern:/(^|[^/])\/(?!\/)(\[.+?]|\\.|[^/\r\n])+\/[gim]{0,3}(?=\s*($|[\r\n,.;})]))/g,lookbehind:!0}}),Prism.languages.markup&&Prism.languages.insertBefore("markup","tag",{script:{pattern:/<script[\w\W]*?>[\w\W]*?<\/script>/gi,inside:{tag:{pattern:/<script[\w\W]*?>|<\/script>/gi,inside:Prism.languages.markup.tag.inside},rest:Prism.languages.javascript},alias:"language-javascript"}});;
Prism.languages.java=Prism.languages.extend("clike",{keyword:/\b(abstract|continue|for|new|switch|assert|default|goto|package|synchronized|boolean|do|if|private|this|break|double|implements|protected|throw|byte|else|import|public|throws|case|enum|instanceof|return|transient|catch|extends|int|short|try|char|final|interface|static|void|class|finally|long|strictfp|volatile|const|float|native|super|while)\b/g,number:/\b0b[01]+\b|\b0x[\da-f]*\.?[\da-fp\-]+\b|\b\d*\.?\d+[e]?[\d]*[df]\b|\W\d*\.?\d+\b/gi,operator:{pattern:/(^|[^\.])(?:\+=|\+\+?|-=|--?|!=?|<{1,2}=?|>{1,3}=?|==?|&=|&&?|\|=|\|\|?|\?|\*=?|\/=?|%=?|\^=?|:|~)/gm,lookbehind:!0}});;
Prism.languages.php=Prism.languages.extend("clike",{keyword:/\b(and|or|xor|array|as|break|case|cfunction|class|const|continue|declare|default|die|do|else|elseif|enddeclare|endfor|endforeach|endif|endswitch|endwhile|extends|for|foreach|function|include|include_once|global|if|new|return|static|switch|use|require|require_once|var|while|abstract|interface|public|implements|private|protected|parent|throw|null|echo|print|trait|namespace|final|yield|goto|instanceof|finally|try|catch)\b/gi,constant:/\b[A-Z0-9_]{2,}\b/g,comment:{pattern:/(^|[^\\])(\/\*[\w\W]*?\*\/|(^|[^:])(\/\/|#).*?(\r?\n|$))/g,lookbehind:!0}}),Prism.languages.insertBefore("php","keyword",{delimiter:/(\?>|<\?php|<\?)/gi,variable:/(\$\w+)\b/gi,"package":{pattern:/(\\|namespace\s+|use\s+)[\w\\]+/g,lookbehind:!0,inside:{punctuation:/\\/}}}),Prism.languages.insertBefore("php","operator",{property:{pattern:/(->)[\w]+/g,lookbehind:!0}}),Prism.languages.markup&&(Prism.hooks.add("before-highlight",function(e){"php"===e.language&&(e.tokenStack=[],e.backupCode=e.code,e.code=e.code.replace(/(?:<\?php|<\?)[\w\W]*?(?:\?>)/gi,function(n){return e.tokenStack.push(n),"{{{PHP"+e.tokenStack.length+"}}}"}))}),Prism.hooks.add("before-insert",function(e){"php"===e.language&&(e.code=e.backupCode,delete e.backupCode)}),Prism.hooks.add("after-highlight",function(e){if("php"===e.language){for(var n,a=0;n=e.tokenStack[a];a++)e.highlightedCode=e.highlightedCode.replace("{{{PHP"+(a+1)+"}}}",Prism.highlight(n,e.grammar,"php"));e.element.innerHTML=e.highlightedCode}}),Prism.hooks.add("wrap",function(e){"php"===e.language&&"markup"===e.type&&(e.content=e.content.replace(/(\{\{\{PHP[0-9]+\}\}\})/g,'<span class="token php">$1</span>'))}),Prism.languages.insertBefore("php","comment",{markup:{pattern:/<[^?]\/?(.*?)>/g,inside:Prism.languages.markup},php:/\{\{\{PHP[0-9]+\}\}\}/g}));;
Prism.languages.bash=Prism.languages.extend("clike",{comment:{pattern:/(^|[^"{\\])(#.*?(\r?\n|$))/g,lookbehind:!0},string:{pattern:/("|')(\\?[\s\S])*?\1/g,inside:{property:/\$([a-zA-Z0-9_#\?\-\*!@]+|\{[^\}]+\})/g}},keyword:/\b(if|then|else|elif|fi|for|break|continue|while|in|case|function|select|do|done|until|echo|exit|return|set|declare)\b/g}),Prism.languages.insertBefore("bash","keyword",{property:/\$([a-zA-Z0-9_#\?\-\*!@]+|\{[^}]+\})/g}),Prism.languages.insertBefore("bash","comment",{important:/(^#!\s*\/bin\/bash)|(^#!\s*\/bin\/sh)/g});;
Prism.languages.python={comment:{pattern:/(^|[^\\])#.*?(\r?\n|$)/g,lookbehind:!0},string:/"""[\s\S]+?"""|("|')(\\?.)*?\1/g,keyword:/\b(as|assert|break|class|continue|def|del|elif|else|except|exec|finally|for|from|global|if|import|in|is|lambda|pass|print|raise|return|try|while|with|yield)\b/g,"boolean":/\b(True|False)\b/g,number:/\b-?(0x)?\d*\.?[\da-f]+\b/g,operator:/[-+]{1,2}|=?&lt;|=?&gt;|!|={1,2}|(&){1,2}|(&amp;){1,2}|\|?\||\?|\*|\/|~|\^|%|\b(or|and|not)\b/g,ignore:/&(lt|gt|amp);/gi,punctuation:/[{}[\];(),.:]/g};;
Prism.languages.sql={comment:{pattern:/(^|[^\\])(\/\*[\w\W]*?\*\/|((--)|(\/\/)|#).*?(\r?\n|$))/g,lookbehind:!0},string:{pattern:/(^|[^@])("|')(\\?[\s\S])*?\2/g,lookbehind:!0},variable:/@[\w.$]+|@("|'|`)(\\?[\s\S])+?\1/g,"function":/\b(?:COUNT|SUM|AVG|MIN|MAX|FIRST|LAST|UCASE|LCASE|MID|LEN|ROUND|NOW|FORMAT)(?=\s*\()/ig,keyword:/\b(?:ACTION|ADD|AFTER|ALGORITHM|ALTER|ANALYZE|APPLY|AS|ASC|AUTHORIZATION|BACKUP|BDB|BEGIN|BERKELEYDB|BIGINT|BINARY|BIT|BLOB|BOOL|BOOLEAN|BREAK|BROWSE|BTREE|BULK|BY|CALL|CASCADE|CASCADED|CASE|CHAIN|CHAR VARYING|CHARACTER VARYING|CHECK|CHECKPOINT|CLOSE|CLUSTERED|COALESCE|COLUMN|COLUMNS|COMMENT|COMMIT|COMMITTED|COMPUTE|CONNECT|CONSISTENT|CONSTRAINT|CONTAINS|CONTAINSTABLE|CONTINUE|CONVERT|CREATE|CROSS|CURRENT|CURRENT_DATE|CURRENT_TIME|CURRENT_TIMESTAMP|CURRENT_USER|CURSOR|DATA|DATABASE|DATABASES|DATETIME|DBCC|DEALLOCATE|DEC|DECIMAL|DECLARE|DEFAULT|DEFINER|DELAYED|DELETE|DENY|DESC|DESCRIBE|DETERMINISTIC|DISABLE|DISCARD|DISK|DISTINCT|DISTINCTROW|DISTRIBUTED|DO|DOUBLE|DOUBLE PRECISION|DROP|DUMMY|DUMP|DUMPFILE|DUPLICATE KEY|ELSE|ENABLE|ENCLOSED BY|END|ENGINE|ENUM|ERRLVL|ERRORS|ESCAPE|ESCAPED BY|EXCEPT|EXEC|EXECUTE|EXIT|EXPLAIN|EXTENDED|FETCH|FIELDS|FILE|FILLFACTOR|FIRST|FIXED|FLOAT|FOLLOWING|FOR|FOR EACH ROW|FORCE|FOREIGN|FREETEXT|FREETEXTTABLE|FROM|FULL|FUNCTION|GEOMETRY|GEOMETRYCOLLECTION|GLOBAL|GOTO|GRANT|GROUP|HANDLER|HASH|HAVING|HOLDLOCK|IDENTITY|IDENTITY_INSERT|IDENTITYCOL|IF|IGNORE|IMPORT|INDEX|INFILE|INNER|INNODB|INOUT|INSERT|INT|INTEGER|INTERSECT|INTO|INVOKER|ISOLATION LEVEL|JOIN|KEY|KEYS|KILL|LANGUAGE SQL|LAST|LEFT|LIMIT|LINENO|LINES|LINESTRING|LOAD|LOCAL|LOCK|LONGBLOB|LONGTEXT|MATCH|MATCHED|MEDIUMBLOB|MEDIUMINT|MEDIUMTEXT|MERGE|MIDDLEINT|MODIFIES SQL DATA|MODIFY|MULTILINESTRING|MULTIPOINT|MULTIPOLYGON|NATIONAL|NATIONAL CHAR VARYING|NATIONAL CHARACTER|NATIONAL CHARACTER VARYING|NATIONAL VARCHAR|NATURAL|NCHAR|NCHAR VARCHAR|NEXT|NO|NO SQL|NOCHECK|NOCYCLE|NONCLUSTERED|NULLIF|NUMERIC|OF|OFF|OFFSETS|ON|OPEN|OPENDATASOURCE|OPENQUERY|OPENROWSET|OPTIMIZE|OPTION|OPTIONALLY|ORDER|OUT|OUTER|OUTFILE|OVER|PARTIAL|PARTITION|PERCENT|PIVOT|PLAN|POINT|POLYGON|PRECEDING|PRECISION|PREV|PRIMARY|PRINT|PRIVILEGES|PROC|PROCEDURE|PUBLIC|PURGE|QUICK|RAISERROR|READ|READS SQL DATA|READTEXT|REAL|RECONFIGURE|REFERENCES|RELEASE|RENAME|REPEATABLE|REPLICATION|REQUIRE|RESTORE|RESTRICT|RETURN|RETURNS|REVOKE|RIGHT|ROLLBACK|ROUTINE|ROWCOUNT|ROWGUIDCOL|ROWS?|RTREE|RULE|SAVE|SAVEPOINT|SCHEMA|SELECT|SERIAL|SERIALIZABLE|SESSION|SESSION_USER|SET|SETUSER|SHARE MODE|SHOW|SHUTDOWN|SIMPLE|SMALLINT|SNAPSHOT|SOME|SONAME|START|STARTING BY|STATISTICS|STATUS|STRIPED|SYSTEM_USER|TABLE|TABLES|TABLESPACE|TEMP(?:ORARY)?|TEMPTABLE|TERMINATED BY|TEXT|TEXTSIZE|THEN|TIMESTAMP|TINYBLOB|TINYINT|TINYTEXT|TO|TOP|TRAN|TRANSACTION|TRANSACTIONS|TRIGGER|TRUNCATE|TSEQUAL|TYPE|TYPES|UNBOUNDED|UNCOMMITTED|UNDEFINED|UNION|UNPIVOT|UPDATE|UPDATETEXT|USAGE|USE|USER|USING|VALUE|VALUES|VARBINARY|VARCHAR|VARCHARACTER|VARYING|VIEW|WAITFOR|WARNINGS|WHEN|WHERE|WHILE|WITH|WITH ROLLUP|WITHIN|WORK|WRITE|WRITETEXT)\b/gi,"boolean":/\b(?:TRUE|FALSE|NULL)\b/gi,number:/\b-?(0x)?\d*\.?[\da-f]+\b/g,operator:/\b(?:ALL|AND|ANY|BETWEEN|EXISTS|IN|LIKE|NOT|OR|IS|UNIQUE|CHARACTER SET|COLLATE|DIV|OFFSET|REGEXP|RLIKE|SOUNDS LIKE|XOR)\b|[-+]{1}|!|[=<>]{1,2}|(&){1,2}|\|?\||\?|\*|\//gi,punctuation:/[;[\]()`,.]/g};;
Prism.languages.ruby=Prism.languages.extend("clike",{comment:/#[^\r\n]*(\r?\n|$)/g,keyword:/\b(alias|and|BEGIN|begin|break|case|class|def|define_method|defined|do|each|else|elsif|END|end|ensure|false|for|if|in|module|new|next|nil|not|or|raise|redo|require|rescue|retry|return|self|super|then|throw|true|undef|unless|until|when|while|yield)\b/g,builtin:/\b(Array|Bignum|Binding|Class|Continuation|Dir|Exception|FalseClass|File|Stat|File|Fixnum|Fload|Hash|Integer|IO|MatchData|Method|Module|NilClass|Numeric|Object|Proc|Range|Regexp|String|Struct|TMS|Symbol|ThreadGroup|Thread|Time|TrueClass)\b/,constant:/\b[A-Z][a-zA-Z_0-9]*[?!]?\b/g}),Prism.languages.insertBefore("ruby","keyword",{regex:{pattern:/(^|[^/])\/(?!\/)(\[.+?]|\\.|[^/\r\n])+\/[gim]{0,3}(?=\s*($|[\r\n,.;})]))/g,lookbehind:!0},variable:/[@$]+\b[a-zA-Z_][a-zA-Z_0-9]*[?!]?\b/g,symbol:/:\b[a-zA-Z_][a-zA-Z_0-9]*[?!]?\b/g});;
Prism.languages.go=Prism.languages.extend("clike",{keyword:/\b(break|case|chan|const|continue|default|defer|else|fallthrough|for|func|go(to)?|if|import|interface|map|package|range|return|select|struct|switch|type|var)\b/g,builtin:/\b(bool|byte|complex(64|128)|error|float(32|64)|rune|string|u?int(8|16|32|64|)|uintptr|append|cap|close|complex|copy|delete|imag|len|make|new|panic|print(ln)?|real|recover)\b/g,"boolean":/\b(_|iota|nil|true|false)\b/g,operator:/([(){}\[\]]|[*\/%^!]=?|\+[=+]?|-[>=-]?|\|[=|]?|>[=>]?|<(<|[=-])?|==?|&(&|=|^=?)?|\.(\.\.)?|[,;]|:=?)/g,number:/\b(-?(0x[a-f\d]+|(\d+\.?\d*|\.\d+)(e[-+]?\d+)?)i?)\b/gi,string:/("|'|`)(\\?.|\r|\n)*?\1/g}),delete Prism.languages.go["class-name"];;
Prism.languages.haskell={comment:{pattern:/(^|[^-!#$%*+=\?&@|~.:<>^\\])(--[^-!#$%*+=\?&@|~.:<>^\\].*(\r?\n|$)|{-[\w\W]*?-})/gm,lookbehind:!0},"char":/'([^\\"]|\\([abfnrtv\\"'&]|\^[A-Z@[\]\^_]|NUL|SOH|STX|ETX|EOT|ENQ|ACK|BEL|BS|HT|LF|VT|FF|CR|SO|SI|DLE|DC1|DC2|DC3|DC4|NAK|SYN|ETB|CAN|EM|SUB|ESC|FS|GS|RS|US|SP|DEL|\d+|o[0-7]+|x[0-9a-fA-F]+))'/g,string:/"([^\\"]|\\([abfnrtv\\"'&]|\^[A-Z@[\]\^_]|NUL|SOH|STX|ETX|EOT|ENQ|ACK|BEL|BS|HT|LF|VT|FF|CR|SO|SI|DLE|DC1|DC2|DC3|DC4|NAK|SYN|ETB|CAN|EM|SUB|ESC|FS|GS|RS|US|SP|DEL|\d+|o[0-7]+|x[0-9a-fA-F]+)|\\\s+\\)*"/g,keyword:/\b(case|class|data|deriving|do|else|if|in|infixl|infixr|instance|let|module|newtype|of|primitive|then|type|where)\b/g,import_statement:{pattern:/(\n|^)\s*(import)\s+(qualified\s+)?(([A-Z][_a-zA-Z0-9']*)(\.[A-Z][_a-zA-Z0-9']*)*)(\s+(as)\s+(([A-Z][_a-zA-Z0-9']*)(\.[A-Z][_a-zA-Z0-9']*)*))?(\s+hiding\b)?/gm,inside:{keyword:/\b(import|qualified|as|hiding)\b/g}},builtin:/\b(abs|acos|acosh|all|and|any|appendFile|approxRational|asTypeOf|asin|asinh|atan|atan2|atanh|basicIORun|break|catch|ceiling|chr|compare|concat|concatMap|const|cos|cosh|curry|cycle|decodeFloat|denominator|digitToInt|div|divMod|drop|dropWhile|either|elem|encodeFloat|enumFrom|enumFromThen|enumFromThenTo|enumFromTo|error|even|exp|exponent|fail|filter|flip|floatDigits|floatRadix|floatRange|floor|fmap|foldl|foldl1|foldr|foldr1|fromDouble|fromEnum|fromInt|fromInteger|fromIntegral|fromRational|fst|gcd|getChar|getContents|getLine|group|head|id|inRange|index|init|intToDigit|interact|ioError|isAlpha|isAlphaNum|isAscii|isControl|isDenormalized|isDigit|isHexDigit|isIEEE|isInfinite|isLower|isNaN|isNegativeZero|isOctDigit|isPrint|isSpace|isUpper|iterate|last|lcm|length|lex|lexDigits|lexLitChar|lines|log|logBase|lookup|map|mapM|mapM_|max|maxBound|maximum|maybe|min|minBound|minimum|mod|negate|not|notElem|null|numerator|odd|or|ord|otherwise|pack|pi|pred|primExitWith|print|product|properFraction|putChar|putStr|putStrLn|quot|quotRem|range|rangeSize|read|readDec|readFile|readFloat|readHex|readIO|readInt|readList|readLitChar|readLn|readOct|readParen|readSigned|reads|readsPrec|realToFrac|recip|rem|repeat|replicate|return|reverse|round|scaleFloat|scanl|scanl1|scanr|scanr1|seq|sequence|sequence_|show|showChar|showInt|showList|showLitChar|showParen|showSigned|showString|shows|showsPrec|significand|signum|sin|sinh|snd|sort|span|splitAt|sqrt|subtract|succ|sum|tail|take|takeWhile|tan|tanh|threadToIOResult|toEnum|toInt|toInteger|toLower|toRational|toUpper|truncate|uncurry|undefined|unlines|until|unwords|unzip|unzip3|userError|words|writeFile|zip|zip3|zipWith|zipWith3)\b/g,number:/\b(\d+(\.\d+)?([eE][+-]?\d+)?|0[Oo][0-7]+|0[Xx][0-9a-fA-F]+)\b/g,operator:/\s\.\s|([-!#$%*+=\?&@|~:<>^\\]*\.[-!#$%*+=\?&@|~:<>^\\]+)|([-!#$%*+=\?&@|~:<>^\\]+\.[-!#$%*+=\?&@|~:<>^\\]*)|[-!#$%*+=\?&@|~:<>^\\]+|(`([A-Z][_a-zA-Z0-9']*\.)*[_a-z][_a-zA-Z0-9']*`)/g,hvariable:/\b([A-Z][_a-zA-Z0-9']*\.)*[_a-z][_a-zA-Z0-9']*\b/g,constant:/\b([A-Z][_a-zA-Z0-9']*\.)*[A-Z][_a-zA-Z0-9']*\b/g,punctuation:/[{}[\];(),.:]/g};;

/* =========================================================================
   Presentation
   ========================================================================= */

(function(moduleName, window) {
    var from = function(selectorOrElement, selectedPlugins) {
            var parent = selectorOrElement.nodeType === 1 ? selectorOrElement : document.querySelector(selectorOrElement),
                slides = [].filter.call(parent.children, function(el) { return el.nodeName !== 'SCRIPT'; }),
                activeSlide = slides[0],
                listeners = {},

                activate = function(index, customData) {
                    if (!slides[index]) {
                        return;
                    }

                    fire('deactivate', createEventData(activeSlide, customData));

                    activeSlide = slides[index];

                    slides.map(deactivate);

                    fire('activate', createEventData(activeSlide, customData));

                    addClass(activeSlide, 'active');
                    removeClass(activeSlide, 'inactive');
                },

                deactivate = function(el, index) {
                    var offset = index - slides.indexOf(activeSlide),
                        offsetClass = offset > 0 ? 'after' : 'before';

                    ['before(-\\d+)?', 'after(-\\d+)?', 'active', 'inactive'].map(removeClass.bind(null, el));

                    el !== activeSlide &&
                        ['inactive', offsetClass, offsetClass + '-' + Math.abs(offset)].map(addClass.bind(null, el));
                },

                slide = function(index, customData) {
                    if (arguments.length) {
                        fire('slide', createEventData(slides[index], customData)) && activate(index, customData);
                    } else {
                        return slides.indexOf(activeSlide);
                    }
                },

                step = function(offset, customData) {
                    var slideIndex = slides.indexOf(activeSlide) + offset;

                    fire(offset > 0 ? 'next' : 'prev', createEventData(activeSlide, customData)) && activate(slideIndex, customData);
                },

                on = function(eventName, callback) {
                    (listeners[eventName] || (listeners[eventName] = [])).push(callback);

                    return function() {
                        listeners[eventName] = listeners[eventName].filter(function(listener) {
                            return listener !== callback;
                        });
                    };
                },

                fire = function(eventName, eventData) {
                    return (listeners[eventName] || [])
                        .reduce(function(notCancelled, callback) {
                            return notCancelled && callback(eventData) !== false;
                        }, true);
                },

                createEventData = function(el, eventData) {
                    eventData = eventData || {};
                    eventData.index = slides.indexOf(el);
                    eventData.slide = el;
                    return eventData;
                },

                deck = {
                    on: on,
                    fire: fire,
                    slide: slide,
                    next: step.bind(null, 1),
                    prev: step.bind(null, -1),
                    parent: parent,
                    slides: slides
                };

            addClass(parent, 'parent');

            slides.map(function(el) {
                addClass(el, 'slide');
            });

            for (var pluginName in selectedPlugins) {
                if (!plugins[pluginName]) {
                    throw Error('Missing plugin: ' + moduleName + '-' + pluginName);
                }
                selectedPlugins[pluginName] !== false && plugins[pluginName](deck, selectedPlugins[pluginName]);
            }

            activate(0);

            decks.push(deck);

            return deck;
        },

        decks = [],

        plugins = {},

        addClass = function(el, cls) {
            el.classList.add(moduleName + '-' + cls);
        },

        removeClass = function(el, cls) {
            el.className = el.className
                .replace(RegExp(moduleName + '-' + cls +'(\\s|$)', 'g'), ' ')
                .trim();
        },

        callOnAllDecks = function(method) {
            return function() {
                var args = arguments;
                decks.map(function(deck) {
                    deck[method].apply(null, args);
                });
            };
        };

    window[moduleName] = {
        from: from,
        slide: callOnAllDecks('slide'),
        next: callOnAllDecks('next'),
        prev: callOnAllDecks('prev'),
        plugins: plugins
    };

}('hyhyhy', window));

hyhyhy.plugins.bullets = function(deck, options) {
    var activeSlideIndex,
        activeBulletIndex,

        bullets = deck.slides.map(function(slide) {
            return [].slice.call(slide.querySelectorAll((typeof options === 'string' ? options : '[data-hyhyhy-bullet]')), 0);
        }),

        next = function() {
            var nextSlideIndex = activeSlideIndex + 1;

            if (activeSlideHasBulletByOffset(1)) {
                activateBullet(activeSlideIndex, activeBulletIndex + 1);
                return false;
            } else if (bullets[nextSlideIndex]) {
                activateBullet(nextSlideIndex, 0);
            }
        },

        prev = function() {
            var prevSlideIndex = activeSlideIndex - 1;

            if (activeSlideHasBulletByOffset(-1)) {
                activateBullet(activeSlideIndex, activeBulletIndex - 1);
                return false;
            } else if (bullets[prevSlideIndex]) {
                activateBullet(prevSlideIndex, bullets[prevSlideIndex].length - 1);
            }
        },

        activateBullet = function(slideIndex, bulletIndex) {
            activeSlideIndex = slideIndex;
            activeBulletIndex = bulletIndex;

            bullets.forEach(function(slide, s) {
                slide.forEach(function(bullet, b) {
                    bullet.classList.add('hyhyhy-bullet');

                    if (s < slideIndex || s === slideIndex && b <= bulletIndex) {
                        bullet.classList.add('hyhyhy-bullet-active');
                        bullet.classList.remove('hyhyhy-bullet-inactive');
                    } else {
                        bullet.classList.add('hyhyhy-bullet-inactive');
                        bullet.classList.remove('hyhyhy-bullet-active');
                    }
                });
            });
        },

        activeSlideHasBulletByOffset = function(offset) {
            return bullets[activeSlideIndex][activeBulletIndex + offset] !== undefined;
        };

    deck.on('next', next);
    deck.on('prev', prev);

    deck.on('slide', function(e) {
        activateBullet(e.index, 0);
    });

    activateBullet(0, 0);
};

hyhyhy.plugins.hash = function(deck) {
    var activeIndex,

        parseHash = function() {
            var hash = window.location.hash.slice(1),
                slideNumberOrName = parseInt(hash, 10);

            if (hash) {
                if (slideNumberOrName) {
                    activateSlide(slideNumberOrName - 1);
                } else {
                    deck.slides.forEach(function(slide, i) {
                        slide.getAttribute('data-hyhyhy-hash') === hash && activateSlide(i);
                    });
                }
            }
        },

        activateSlide = function(index) {
            if (index !== activeIndex) {
                deck.slide(index);
            }
        };

    setTimeout(function() {
        parseHash();

        deck.on('activate', function(e) {
            var slideName = e.slide.getAttribute('data-hyhyhy-hash');
            window.location.hash = slideName || e.index + 1;
            activeIndex = e.index;
        });

        window.addEventListener('hashchange', parseHash);
    }, 0);
};

hyhyhy.plugins.keys = function(deck, options) {
    var isHorizontal = options === true || options == 'horizontal';

    document.addEventListener('keydown', function(e) {
        (
            e.which == 34 || // PAGE DOWN
            e.which == 32 || // SPACE
            isHorizontal && e.which == 39 || // RIGHT
            !isHorizontal && e.which == 40 // DOWN
        ) && deck.next();
        (
            e.which == 33 || // PAGE UP
            isHorizontal && e.which == 37 || // LEFT
            !isHorizontal && e.which == 38 // UP
        ) && deck.prev();
    });
};

hyhyhy.plugins.fullscreen = function(deck) {
    function launchFullscreen() {
        if(
            document.documentElement.requestFullscreen
        ){
            document.documentElement.requestFullscreen();
        }else if(
            document.documentElement.mozRequestFullScreen
        ){
            document.documentElement.mozRequestFullScreen();
        }else if(
            document.documentElement.webkitRequestFullscreen
        ){
            document.documentElement.webkitRequestFullscreen();
        }else if(
            document.documentElement.msRequestFullscreen
        ){
            document.documentElement.msRequestFullscreen();
        }
    }

    document.addEventListener('keydown', function(e) {
        (
            e.which == 72 // h KEY
        ) && launchFullscreen();
    });
};

hyhyhy.plugins.progress = function (deck, options) {
    var progressParent = document.createElement('div'),
        progressBar = document.createElement('div'),
        prop = options === 'vertical' ?
            'height' :
            ['horizontal', true].indexOf(options) + 1 ?
                'width' :
                undefined;

    if (!prop) {
        return;
    }

    progressParent.className = 'hyhyhy-progress-parent';
    progressBar.className = 'hyhyhy-progress-bar';
    progressParent.appendChild(progressBar);
    deck.parent.appendChild(progressParent);

    deck.on('activate', function(e) {
        progressBar.style[prop] = (e.index * 100 / (deck.slides.length - 1)) + '%';
    });
};

hyhyhy.plugins.scale = function(deck, options) {
    var parent = deck.parent,
        firstSlide = deck.slides[0],
        slideHeight = firstSlide.offsetHeight,
        slideWidth = firstSlide.offsetWidth,
        useZoom = options === 'zoom' || ('zoom' in parent.style && options !== 'transform'),

        wrap = function(element) {
            var wrapper = document.createElement('div');
            wrapper.className = 'hyhyhy-scale-parent';
            parent.insertBefore(wrapper, element);
            wrapper.appendChild(element);
            return wrapper;
        },

        elements = useZoom ? deck.slides : deck.slides.map(wrap),

        transformProperty = (function(property) {
            var prefixes = 'Moz Webkit O ms'.split(' ');
            return prefixes.reduce(function(currentProperty, prefix) {
                    return prefix + property in parent.style ? prefix + property : currentProperty;
                }, property.toLowerCase());
        }('Transform')),

        scale = useZoom ?
            function(ratio, element) {
                element.style.zoom = ratio;
            } :
            function(ratio, element) {
                element.style[transformProperty] = 'scale(' + ratio + ')';
            },

        scaleAll = function() {
            var xScale = parent.offsetWidth / slideWidth,
                yScale = parent.offsetHeight / slideHeight;

            elements.forEach(scale.bind(null, Math.min(xScale, yScale)));
        };

    window.addEventListener('resize', scaleAll);
    scaleAll();
};

hyhyhy.plugins.state = function(deck) {
    var modifyState = function(method, event) {
        var attr = event.slide.getAttribute('data-hyhyhy-state');

        if (attr) {
            attr.split(' ').forEach(function(state) {
                state && deck.parent.classList[method](state);
            });
        }
    };

    deck.on('activate', modifyState.bind(null, 'add'));
    deck.on('deactivate', modifyState.bind(null, 'remove'));
};

hyhyhy.plugins.touch = function(deck, options) {
    var axis = options === true || options == 'horizontal' ? 'X' : 'Y',
        startPosition,
        delta;

    deck.parent.addEventListener('touchstart', function(e) {
        if (e.touches.length == 1) {
            startPosition = e.touches[0]['page' + axis];
            delta = 0;
        }
    });

    deck.parent.addEventListener('touchmove', function(e) {
        if (e.touches.length == 1) {
            e.preventDefault();
            delta = e.touches[0]['page' + axis] - startPosition;
        }
    });

    deck.parent.addEventListener('touchend', function() {
        Math.abs(delta) > 50 && (delta > 0 ? deck.prev() : deck.next());
    });
};