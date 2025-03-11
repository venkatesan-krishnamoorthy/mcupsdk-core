const { template } = require('lodash');
let path = require('path');

let device = "am263px";

const files = {
    common: [
        "ocmc_benchmarking.c",
        "main.c",
    ],
};

const projectspecfiles = {
    common: [
        "ocmc_benchmarking.h",
        "annotations.S"
    ],
};
const readmeDoxygenPageTag = "EXAMPLES_OPTIFLASH_XIP_SP_BENCHMARK";

/* Relative to where the makefile will be generated
 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>
 */
const filedirs = {
    common: [
        "..",       /* core_os_combo base */
        "../../..", /* Example base */
    ],
};

const asmFiles = {
    common: [
        "annotations.S"
    ]
};

const libdirs_freertos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am263px/r5f",
    ],
};

const libs_freertos_r5f = {
    common: [
        "freertos.am263px.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am263px.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const lflags = {
    common:[

    ]
};

const cflags = {
    common:[
        "-fno-common"
    ]
};

const syscfgfile = "../example.syscfg";

const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am263px-cc", os: "freertos", isPartOfSystemProject: false},
];

var template_options = {
    is_baseline: false,
    enable_l2_cache: true,
    cache: "64k",
    sp: true
}

const templates =
[
    {
        input: ".project/templates/am263px/optiflash_benchmark/ocmc_benchmarking.c.xdt",
        output: "../../../ocmc_benchmarking.c",
        options: template_options
    },
    {
        input: ".project/templates/am263px/optiflash_benchmark/ocmc_benchmarking.h.xdt",
        output: "../../../ocmc_benchmarking.h",
        options: template_options
    },
    {
        input: ".project/templates/am263px/optiflash_benchmark/ocmc_main.c.xdt",
        output: "../main.c",
        options: template_options
    },
    {
        input: ".project/templates/am263px/optiflash_benchmark/annotations.S.xdt",
        output: "../../../annotations.S",
        options: template_options
    },
    {
        input: ".project/templates/am263px/optiflash_benchmark/example.syscfg.xdt",
        output: "../example.syscfg",
        options: template_options
    },
];

const systemProjects = [];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "optiflash_xip_smart_placement_benchmark";
    property.isInternal = false;
    property.description = "An OCRAM memory benchmark."
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.projectspecfiles = projectspecfiles;
    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.asmfiles = asmFiles;
    build_property.includes = includes_freertos_r5f;
    build_property.libdirs = libdirs_freertos;
    build_property.libs = libs_freertos_r5f;
    build_property.lflags = lflags;
    build_property.cflags = cflags;
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;
    build_property.templates = templates;
    return build_property;
}

function getSystemProjects(device)
{
    return systemProjects;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
    getSystemProjects,
};
