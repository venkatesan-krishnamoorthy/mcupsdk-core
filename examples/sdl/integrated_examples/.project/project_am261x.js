let path = require('path');

let device = "am261x";

const files = {
    common: [
        "dcc_uc1.c",
        "main.c",
        "dpl_interface.c",
        "mcan_loopback_polling.c",
        "mcan_task.c",
        "main_task.c",
        "main_parent_task.c",
        "stc_main_r5f.c",
        "pbist.c",
        "esm.c",
        "ccm.c",
        "rti_uc1.c",
        "rti_uc2.c",
        "rundiags.c",
        "ecc_mcan.c",
        "ecc_icssm.c",
        "ecc_mssl2.c",
        "ecc_atcm.c",
        "ecc_btcm.c",
        "ecc_tptc.c",
        "parity_tcm.c",
        "parity_dma.c",
        "mcrc_automode.c",
        "tmu_rom_checksum.c",
        "vtm_main.c",
        "tmu_parity.c",
        "tog_main.c",
        "ecc_bus_safety_main.c",
        "ecc_bus_safety_common.c",
        "ecc_bus_safety_Interrupt.c",
    ],
};

const asmfiles_r5f = {
    common: [
		"resetvecs.S",
	],
};

const projectspecfiles = {
    common: [
        "resetvecs.S",
    ],
};

/* Relative to where the makefile will be generated
 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>
 */
const filedirs = {
    common: [
        "..",       /* core_os_combo base */
        "../../..", /* Example base */
        "../../../sdl",
        "../../../../../dpl", /* SDL dpl base add an extra lvl*/
        "../../../../../integrated_examples/sdl",
    ],
};

const libdirs_freertos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/sdl/lib",
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am261x/r5f",
        "${MCU_PLUS_SDK_PATH}/examples/sdl/integrated_examples",
        "${MCU_PLUS_SDK_PATH}/examples/sdl/integrated_examples/sdl",
    ],
};

const libs_freertos_r5f = {
    common: [
        "freertos.am261x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am261x.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am261x.r5f.ti-arm-clang.${ConfigName}.lib",
        "sdl.am261x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const defines_r5f = {
    common: [
        "SUBSYS_MSS",
        "R5F0_INPUTS",

    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg"

const readmeDoxygenPageTag = "EXAMPLES_SDL_CCM";

const templates_freertos_r5f =
[
    {
        input: ".project/templates/am261x/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "main_parent",
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am261x-som", os: "freertos"},
];

function getComponentProperty(device) {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "mcan_sdl";
    property.isInternal = false;
    property.tirexResourceSubClass = [ "example.gettingstarted" ];
    property.description = "This example verifies all diagnostic along with mcan example"
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.projectspecfiles = projectspecfiles;
    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.defines = defines_r5f;
    build_property.syscfgfile = syscfgfile;
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;

    if(buildOption.cpu.match(/r5f*/))
    {
        if(buildOption.os.match(/freertos*/) )
        {
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_r5f;
            build_property.templates = templates_freertos_r5f;
            build_property.asmfiles = asmfiles_r5f;
        }
        
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
