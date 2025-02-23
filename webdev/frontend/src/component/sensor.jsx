import {useState,useEffect} from "react";
const Sensor=()=>{
    const [value,setValue]=useState(0);
    useEffect(()=>{
        setValue(value)
    },[]);

    return(
        <div className="min-h-screen bg-gray-100"></div>
    );
}
export default Sensor;