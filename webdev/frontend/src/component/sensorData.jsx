import { useEffect, useState } from "react";
import DonutChart from "./test.jsx";
let data;
import FormControlLabel from '@mui/material/FormControlLabel';
import Switch from '@mui/material/Switch';

let temp_val=0;
let perciptate_val=0;
let humidity_val=0;
const temp = async () => {
    try {
        const response = await fetch("https://api.openweathermap.org/data/2.5/weather?lat=29.9534804&lon=76.8146376&appid=89426cce37c0080d35b7780c2b4bfe1f");
        if (!response.ok) throw new Error("Failed to fetch data");
        data = await response.json();

        temp_val=data.main.temp;
        perciptate_val = data.rain?.["1h"] || 0;
        humidity_val=data.main.humidity||0;


    } catch (error) {
        console.error("Error fetching sensor data:", error);
    }
};

temp()
const SensorData = () => {
    const [sensorData, setSensorData] = useState([]);
    const [response,setResponse] = useState({});
    const [switchStates, setSwitchStates] = useState([false, false, false, false]);

    const [motorStatus, setMotorStatus] = useState(null);


        const fetchMotorStatus = async () => {
            try {
                const response = await fetch("https://9fx3gmg3-3000.inc1.devtunnels.ms/motor-status");
                const data = await response.json();

                if (data && data.motor_status) {
                    for(let i = 0; i < data.motor_status.length; i++) {
                        switchStates[i]=data.motor_status[i];

                    }

                } else {
                    console.error("Error: No motor status received.");
                }
            } catch (error) {
                console.error("Error fetching motor status:", error);
            }
        };

        setInterval(fetchMotorStatus(),2000);


    const handleClick = async (num) => {
        try {
            const updatedStates = [...switchStates];
            updatedStates[num] = !updatedStates[num];

            const res = await fetch("https://9fx3gmg3-3000.inc1.devtunnels.ms/data", {
                method: "POST",
                headers: {
                    "Content-Type": "application/json",
                },
                body: JSON.stringify(updatedStates ),
            });

            setSwitchStates(updatedStates);
        } catch (error) {
            console.error("Error:", error);
        }
    };


    useEffect(() => {
        const fetchData = async () => {
            try {
                const response = await fetch("https://smartirrigationbackend.onrender.com/get-command");
                if (!response.ok) throw new Error("Failed to fetch data");
                data = await response.json();
                // console.log(data[data.length - 1]);

                setSensorData(data[data.length-1].sensors || []);
                // console.log(data[data.length-1].sensors[0].temperature);
            } catch (error) {
                console.error("Error fetching sensor data:", error);
            }
        };

        fetchData();
        const interval = setInterval(fetchData, 2000);

        return () => clearInterval(interval);
    }, []);
    return (
        <>
            <div className={"flex justify-center  pt-8 text-3xl"}><h1  className={"backdrop-blur"} style={{width:"max-content"}}>Smart Irrigation</h1></div>
    <div style={{width: "100%", height: "50rem"}} className={"flex"}>




            <div className="min-h-screen  flex justify-center text-white items-center rounded-xl -mt-16">

                <table className="border-collapse border border-gray-500 w-[500px] h-[500px] backdrop-blur-sm rounded-xl" >
                    <tbody>
                    <tr className="border border-gray-500">
                        <td className="border border-gray-500 p-4 w-[250px] h-[250px] text-center">
                            <h1 className={"-ml-48"}>Crop-1</h1>
                            <DonutChart percentage={(() => {
                                try {
                                    return sensorData[0].moisture;
                                } catch (err) {
                                    return 0;
                                }
                            })()} name={"Crop-1"}/>

                            <FormControlLabel
                                sx={{ display: 'block' }}
                                control={
                                    <Switch
                                        checked={switchStates[0]}
                                        onClick={()=>handleClick(0)}
                                        name="Pump"
                                        color="primary"
                                    />
                                }
                                label="Pump"
                            />
                        </td>
                        <td className="border border-gray-500 p-4 w-[250px] h-[250px] text-center">
                            <h1 className={"-ml-48"}>Crop-2</h1>
                            <DonutChart percentage={(() => {
                                try {
                                    return sensorData[1].moisture;
                                } catch (err) {
                                    return 0;
                                }
                            })()} name={"Crop-2"} />
                            <FormControlLabel
                                sx={{ display: 'block' }}
                                control={
                                    <Switch
                                        checked={switchStates[1]}
                                        onChange={()=>handleClick(1)}
                                        name="Pump"
                                        color="primary"
                                    />
                                }
                                label="Pump"
                            />

                        </td>
                    </tr>
                    <tr className="border border-gray-500">
                        <td className="border border-gray-500 p-4 w-[250px] h-[250px] text-center">
                            <h1 className={"-ml-48"}>Crop-3</h1>
                            <DonutChart percentage={(() => {
                                try {
                                    return sensorData[2].moisture;
                                } catch (err) {
                                    return 0;
                                }
                            })()} name={"Crop-3"}/>

                            <FormControlLabel
                                sx={{display: 'block'}}
                                control={
                                    <Switch
                                        checked={switchStates[2]}
                                        onClick={() => handleClick(2)}
                                        name="Pump"
                                        color="primary"
                                    />
                                }
                                label="Pump"
                            />

                        </td>
                        <td className="border border-gray-500 p-4 w-[250px] h-[250px] text-center">

                            <h1 className={"-ml-48"}>Crop-4</h1>
                            <DonutChart percentage={(() => {
                                try {
                                    return sensorData[3].moisture;
                                } catch (err) {
                                    return 0;
                                }
                            })()} name={"Crop-4"}/>

                            <FormControlLabel
                                sx={{display: 'block'}}
                                control={
                                    <Switch
                                        checked={switchStates[3]}
                                        onClick={() => handleClick(3)}
                                        name="Pump"
                                        color="primary"
                                    />
                                }
                                label="Pump"
                            />

                        </td>
                    </tr>
                    </tbody>
                </table>
            </div>

            <div style={{width: "60%", height: "100%"}} >
                <div className={"flex-col mt-16 backdrop-blur text-white"} style={{height:"30%",marginLeft:"80% "}}>
                <DonutChart percentage={Math.floor(temp_val-273)} name={"Temperature"}/>
                <DonutChart percentage={perciptate_val} name={"Percipitate"}/>
                    <DonutChart percentage={humidity_val} name={"Humidity"}/>
                </div>
                <div>

                </div>
            </div>


    </div>
        </>
    );
};

export default SensorData;
