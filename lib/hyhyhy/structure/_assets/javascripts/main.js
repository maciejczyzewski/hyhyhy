/*!                          main.js | © 2014 hyhyhy                        !*/

/* =========================================================================
   Configure
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
                    first: slide.bind(null, 0),
                    last: slide.bind(null, slides.length - 1),
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
        first: callOnAllDecks('first'),
        last: callOnAllDecks('last'),
        plugins: plugins
    };

}('hyhyhy', window));

/* =========================================================================
   Presentation
   ========================================================================= */

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
    var isHorizontal = options === true || options == 'horizontal',
        keyList = [];

    var pushToQueue = function(list, limit, v) {
        if (list.length === limit) {
            list.splice(-2, 1);
        }
        list.push(v);
        return list;
    };

    var isEqual = function(arr1, arr2) {
      return JSON.stringify(arr1) === JSON.stringify(arr2);
    };

    document.addEventListener('keydown', function(e) {
        var withMod = e.shiftKey || e.altKey || e.ctrlKey || e.metaKey;

        (
            e.which == 34 || // PAGE DOWN
            e.which == 32 || // SPACE
            e.which == 74 || // j
            isHorizontal && e.which == 39 || // RIGHT
            !isHorizontal && e.which == 40 // DOWN
        ) && deck.next();
        (
            e.which == 33 || // PAGE UP
            e.which == 75 || // k
            isHorizontal && e.which == 37 || // LEFT
            !isHorizontal && e.which == 38 // UP
        ) && deck.prev();
        (
            // GG
            isEqual([71, 71], pushToQueue(keyList, 2, !withMod ? e.which : null))
        ) && deck.first();
        (
            e.which == 71 && e.shiftKey // SHIFT + G
        ) && deck.last();
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

    // Experiment - WP8 support (@aiboy)
    deck.parent.addEventListener('MSPointerDown', function(e) {
        if (e.touches.length == 1) {
            startPosition = e.touches[0]['page' + axis];
            delta = 0;
        }
    });

    deck.parent.addEventListener('MSPointerMove', function(e) {
        if (e.touches.length == 1) {
            e.preventDefault();
            delta = e.touches[0]['page' + axis] - startPosition;
        }
    });

    deck.parent.addEventListener('MSPointerUp', function() {
        Math.abs(delta) > 50 && (delta > 0 ? deck.prev() : deck.next());
    });
};
