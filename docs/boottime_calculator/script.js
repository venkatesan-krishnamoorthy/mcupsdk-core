
// Application size and secure boot time values 

//For AM263x
const am263x_mcelf_signed_appsizes = [64, 128, 256, 512, 768, 1024, 1536];
const am263x_mcelf_signed_boottime = [43.0414, 46.6608, 53.9363, 68.3982, 82.9368, 97.3231, 126.6949];


const am263x_mcelf_encrypted_appsizes = [64, 128, 256, 512, 768, 1024, 1536];
const am263x_mcelf_encrypted_boottime = [44.9173, 50.1876, 60.7206, 81.6829, 102.6271, 123.5777, 165.8423];

//For AM263Px

//28.7848 + 0.00813173 x
const am263px_mcelf_signed_appsizes = [64, 128, 256, 512, 768, 1024, 1536, 2048, 2560];
const am263px_mcelf_signed_boottime = [31.0843, 31.5388, 32.5709, 34.0032, 36.4543, 39.7178, 43.8362, 48.9356, 53.1759];

// y = 28.8668 + 0.0336063 x
const am263px_mcelf_encrypted_appsizes = [64, 128, 256, 512, 768, 1024, 1536, 2048, 2560];
const am263px_mcelf_encrypted_boottime = [32.3598, 35.1382, 38.7572, 47.4955, 56.5441, 66.4885, 83.5779, 101.8362, 119.8195];


// Information Table

const am263x_software_table = ` Software Specifications
<table>
<tr><td>MCU+ SDK version</td><td>v10.02.00</td></tr>  
<tr><td>TIFSMCU version</td><td>v10.02.00</td></tr>  
<tr><td>Application Image Format version</td><td>MCELF</td></tr>  
<tr><td>SBL Size</td><td>44KB</td></tr>  
<tr><td>SBL Properties</td><td>Signed + Encrypted</td></tr>  
<tr><td>HSM Runtime Size</td><td>72KB</td></tr>  
<tr><td>HSM Runtime Properties</td><td>Signed + Encrypted</td></tr>  
<tr><td>Maximum Segment of Application</td><td>64KB</td></tr> 
</table>
`;

const am263px_software_table = ` Software Specifications
<table>
<tr><td>MCU+ SDK version</td><td>v10.02.00</td></tr>  
<tr><td>TIFSMCU version</td><td>v10.02.00</td></tr>  
<tr><td>Application Image Format version</td><td>MCELF</td></tr>  
<tr><td>SBL Size</td><td>60KB</td></tr>
<tr><td>SBL Properties</td><td>Signed + Encrypted</td></tr>    
<tr><td>HSM Runtime Size</td><td>62KB</td></tr>
<tr><td>HSM Runtime Properties</td><td>Signed + Encrypted</td></tr>    
<tr><td>Maximum Segment of Application</td><td>64KB</td></tr> 
</table>
`;

const am263x_hardware_table = ` <br>
Hardware Specifications
<table>
<tr><td>Application Core Frequency</td><td>400 MHz</td></tr>  
<tr><td>Flash Frequency</td><td>80 MHz</td></tr>
<tr><td>Flash Properties</td><td>Quad SPI Flash Interface with SDR</td></tr>
<tr><td>HSM Frequency </td><td>200 MHz</td></tr>  
</table>
`;

const am263px_hardware_table = ` <br>
Hardware Specifications
<table>
<tr><td>Application Core Frequency</td><td>400 MHz</td></tr>  
<tr><td>Flash Frequency</td><td>133 MHz</td></tr>
<tr><td>Flash Properties</td><td>Octal SPI Flash Interface with DDR support</td></tr>
<tr><td>HSM Frequency </td><td>200 MHz</td></tr>  
</table>
`;

function onSubmitInfo() {
    xValues1 = [];
    yValues1 = [];

    xValues2 = [];
    yValues2 = [];

    if (document.getElementById("mySOC").value === "am263px") {
        console.log(document.getElementById("mySOC").value)
        xValues1 = am263px_mcelf_signed_appsizes;
        yValues1 = am263px_mcelf_signed_boottime;

        xValues2 = am263px_mcelf_encrypted_appsizes;
        yValues2 = am263px_mcelf_encrypted_boottime;

        document.getElementById('table-container').innerHTML = am263px_software_table + am263px_hardware_table;
    }
    else {
        xValues1 = am263x_mcelf_signed_appsizes;
        yValues1 = am263x_mcelf_signed_boottime;

        xValues2 = am263x_mcelf_encrypted_appsizes;
        yValues2 = am263x_mcelf_encrypted_boottime;

        document.getElementById('table-container').innerHTML = am263x_software_table + am263x_hardware_table;
    }

    new Chart("myChart", {
        type: "line",
        data: {
            labels: xValues1,
            datasets: [{
                label: "Authenticated Boot",
                fill: false,
                lineTension: 0,
                backgroundColor: "rgba(28, 6, 160, 0.8)",
                borderColor: "rgba(28, 6, 160, 0.8)",
                data: yValues1
            },
            {
                label: "Authenticated + Decrypted Boot",
                fill: false,
                lineTension: 0,
                backgroundColor: "rgba(18, 96, 45, 0.8)",
                borderColor: "rgba(18, 96, 45, 0.8)",
                data: yValues2
            }
            ]
        },
        options: {
            legend: {
                display: true
            },
            scales: {
                xAxes: [
                    {
                        scaleLabel: {
                            display: true,
                            labelString: 'Application Size in KB'
                        }
                    }
                ],
                yAxes: [
                    {
                        scaleLabel: {
                            display: true,
                            labelString: 'Boot time in milliseconds'
                        }
                    }],
            },
            plugins: {
                title: {
                    display: true,
                    text: 'Custom Chart Title',
                    position: 'bottom',
                    padding: {
                        top: 10,
                        bottom: 30
                    }
                }
            }
        }
    });
}
