module.exports = function(grunt) {
    grunt.initConfig({
        pkg: grunt.file.readJSON('package.json'),
        htmlcompressor: {
            default: {
                files: [{
                    './generated/client.html': './client.html'
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

    grunt.registerTask('default', ['htmlcompressor']);

};