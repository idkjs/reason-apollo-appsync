open Types;
let str = React.string;
[@react.component]
let make = (~iceCream) =>
  <tr>
    <td> {str(iceCream.name)} </td>
    <td> {str(iceCream.description)} </td>
  </tr>;