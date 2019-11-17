open ApolloHooks;
open Types;
module TicketsQuery = [%graphql
  {|
  query ListIceCreams {
    listIceCreams{
      items{
        id
        name
        description
        rating
      }
    }
  }
|}
];


// external toConfigType: Js.Json.t => TicketsQuery.t = "%identity";
// external toJson: TicketsQuery.t => Js.Json.t = "%identity";

let limit = 2;
let makeIceCream: Js.t('a) => iceCream =
  data => {
    name: data##name,
    id: data##id,
    description: data##description,
    rating: data##rating,
  };
[@react.component]
let make = () => {
  let (_, fullResult) =
    useQuery(
      ~variables=TicketsQuery.make()##variables,
      ~notifyOnNetworkStatusChange=true,
      (module TicketsQuery),
    );

  <div className="card">
    <div className="card-body">
      <h4 className="card-title"> {React.string("Recent Tickets")} </h4>
      <div className="table-responsive">
        <table className="table">
          <thead>
            <tr>
              <th> {React.string("Assignee")} </th>
              <th> {React.string("Subject")} </th>
              <th> {React.string("Status")} </th>
              <th> {React.string("Last Update")} </th>
              <th> {React.string("Tracking ID")} </th>
            </tr>
          </thead>
          {switch (fullResult) {
           | {loading: true, data: None} => React.null
           | {data: Some(data)} =>
             let data =
               data##listIceCreams
               ->Belt.Option.flatMap(listItems => listItems##items)
               ->Belt.Option.getWithDefault([||]);
             Js.log2("data", data);
             let iceCreams =
               data
               ->Belt.Array.keep(Belt.Option.isSome)
               ->Belt.Array.map(Belt.Option.getExn)
               ->Belt.Array.map(makeIceCream);

             <tbody>
               {iceCreams->Belt.Array.map(iceCream =>
                  <IceCreamItem key={iceCream.id} iceCream />
                )
                |> React.array}
             </tbody>;
           | {error: Some(error)} =>
             <div> {ReasonReact.string(error##message)} </div>
           | {error: None, data: None, loading: false} =>
             React.string("Not asked")
           }}
        </table>
      </div>
    </div>
  </div>;
};