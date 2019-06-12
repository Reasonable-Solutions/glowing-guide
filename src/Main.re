/* State declaration */
type state = {file: string, title: string};

/* Action declaration */
type action =
  | Upload(string)
  | UpdateText(string);

module Styles = {
  open Css;
  global("body", [margin(px(-1))]);
  global("*", [boxSizing(borderBox), fontFamily("Helvetica Neue, Segoe UI, arial, sans-serif")]);

  let main = style([display(flexBox), background(Theme.grey)]);
  let sidebar = style([borderRight(px(1), solid, hex("d1d8db")), width(px(340))]);
  let content = style([]);
};

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | Upload(url) => {...state, file: url}
        | UpdateText(title) => {...state, title: title}
        },
      {file: "", title: "foo"},
    );
  <div className=Styles.main>
    <div className=Styles.sidebar>
      <Expander title="Image upload">
        <Upload upload={e => dispatch(Upload(e))}/>
      </Expander>
       <Expander title="Title">
        <div> <input type_="text" placeholder="Title text" onChange={e => dispatch(UpdateText(ReactEvent.Form.target(e)##value))}/>  </div>
      </Expander>
    </div>
    <div className=Styles.content> {ReasonReact.string("content")} </div>
    <img src={state.file}/>
    <h1>{ReasonReact.string(state.title)}</h1>
  </div>;
};
