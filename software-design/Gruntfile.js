module.exports = function(grunt) {
    grunt.initConfig({
        pkg: grunt.file.readJSON('package.json'),
        copy: {
            default: {
                files: [{
                    src: './client.html',
                    dest: './generated/client.html'
                }]
            }
        },
        replace: {
            pre: {
                src: './generated/client.html',
                overwrite: true, 
                replacements: [{
                    from: /(name="([^"]*)".*)value="[^"]*"/ig,
                    to: '$1value="));out.concat(_register.$2);out.concat(F("'
                }]
            },
            post: {
                src: './generated/client.html',
                overwrite: true, 
                replacements: [{
                    from: /"/g,
                    to: '\\"'
                }, {
                    from: /(\)\);out\.concat\(_register\.[^\)]+\);out.concat\(F\()/g,
                    to: '"$1"'
                }, {
                    from: /^/g,
                    to: 'out.concat(F("'
                }, {
                    from: /$/g,
                    to: '"));'
                }, {
                    from: /(out\.concat\()/g,
                    to: '\n  $1'
                }]
            }
        },
        htmlcompressor: {
            default: {
                files: [{
                    './generated/client.html': './generated/client.html'
                }],
                options: {
                    'compress-js': true,
                    'compress-css': true,
                    'remove-intertag-spaces': true,
                    'remove-js-protocol': true,
                    'remove-script-attr': true,
                    'remove-style-attr': true,
                    'remove-quotes': true
                }
            }
        }
    });

    grunt.loadNpmTasks('grunt-htmlcompressor');
    grunt.loadNpmTasks('grunt-text-replace');
    grunt.loadNpmTasks('grunt-contrib-copy');

    grunt.registerTask('default', ['copy', 'replace:pre', 'htmlcompressor', 'replace:post']);

};