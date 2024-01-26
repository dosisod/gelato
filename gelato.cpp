#include <iostream>

#include <gcc-plugin.h>
#include <plugin-version.h>
#include <print-tree.h>
#include <tree.h>

int plugin_is_GPL_compatible;

static struct plugin_info gelato_plugin_info = {
	.version = "0.0.0",
	.help = "Create user-defined attributes in C++",
};

// TODO: see what the lowest version I can use is (just chose my current build)
static struct plugin_gcc_version gelato_plugin_ver = { .basever = "13.2.1" };

static tree attr_call_handler(tree *node, tree name, tree args, int flags, bool *no_add_attrs) {
	// TODO: Modify AST tree to handle attributes accordingly

	return *node;
}

static struct attribute_spec test_attribute = {
	.name = "test",
	.min_length = 0,
	.max_length = -1,
	.handler = attr_call_handler,
};

static struct attribute_spec fixture_attribute = {
	.name = "fixture",
	.min_length = 0,
	.max_length = -1,
	.handler = attr_call_handler,
};

static struct attribute_spec yield_attribute = {
	.name = "yield",
	.min_length = 0,
	.max_length = -1,
	.handler = attr_call_handler,
};

static void register_attributes(void *gcc_data, void *user_data) {
	register_attribute(&test_attribute);
	register_attribute(&fixture_attribute);
	register_attribute(&yield_attribute);
}

static void handle_attributes(void *gcc_data, void *user_data) {
	tree ast = (tree)gcc_data;

	debug_tree(ast);
}

int plugin_init(
	struct plugin_name_args *plugin_info,
	struct plugin_gcc_version *version
) {
	if (strncmp(gelato_plugin_ver.basever, version->basever, strlen(version->basever))) {
		return 1;
	}

	if (!plugin_default_version_check(version, &gcc_version)) {
		return 1;
	}

	register_callback(plugin_info->base_name, PLUGIN_INFO, NULL, &gelato_plugin_info);
	register_callback(plugin_info->base_name, PLUGIN_ATTRIBUTES, register_attributes, NULL);
	register_callback(plugin_info->base_name, PLUGIN_PRE_GENERICIZE, handle_attributes, NULL);

	return 0;
}
