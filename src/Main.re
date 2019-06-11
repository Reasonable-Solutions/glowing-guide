/* State declaration */
type state = {file: string};

/* Action declaration */
type action =
  | Upload(string);

module Styles = {
  open Css;
  global("body", [margin(px(-1))]);
  let main = style([display(flexBox), background(rgba(60, 60, 60, 0.1))]);
  let sidebar = style([]);
  let content = style([]);
};

/* <div className=Styles.card>
     <h1 className=Styles.title> (ReasonReact.stringToElement("Hello")) </h1>
     <button className=Styles.actionButton(false)>
   </div> */

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (_state, action) =>
        switch (action) {
        | Upload(url) => {file: url}
        },
      {file: ""},
    );
  <div className=Styles.main>
    <div className=Styles.sidebar>
      <Expander title="image upload">
        <Upload upload={e => dispatch(Upload(e))}/>
      </Expander>
       <Expander title="expander">
        <div> {ReasonReact.string("expanderChildren")} </div>
      </Expander>
    </div>
    <div className=Styles.content> {ReasonReact.string("content")} </div>
    <img src={state.file}/>
  </div>;
};
