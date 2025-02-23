import React from "react";
import { PieChart, Pie, Cell } from "recharts";


const DonutChart = ({percentage,name}) => {

    const completedValue = (percentage / 100) * 270;
    const remainingValue = 270 - completedValue;

    const data = [
        { name: "Completed", value: completedValue },
    ];
    return (
        <div className="flex flex-col justify-center items-center">
            <PieChart width={250} height={250}>

                <Pie
                    data={[{ value: 270 }]}
                    cx="50%"
                    cy="50%"
                    innerRadius={80}
                    outerRadius={100}
                    startAngle={225}
                    endAngle={-45}
                    dataKey="value"
                    fill="#E0E0E0"
                    stroke="none"
                    cornerRadius={10}
                />

                <Pie
                    data={data}
                    cx="50%"
                    cy="50%"
                    innerRadius={80}
                    outerRadius={100}
                    startAngle={225}
                    endAngle={225-completedValue}
                    dataKey="value"
                    stroke="none"
                    cornerRadius={10} // Rounded edges
                >
                    <Cell fill={percentage<=25?"red":percentage<=85?"#49F41CFF":"blue"} />
                </Pie>
            </PieChart>


            <h2 className=" font-bold -mt-40 " style={{fontSize:"36px"}}>{percentage}</h2>
            <h2>{name}</h2>

        </div>
    );
};

export default DonutChart;
