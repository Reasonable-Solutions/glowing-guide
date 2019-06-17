type action =
  | Update(string);
type state = {text: string};
module Styles = {
  let t = 5;
};

[@react.component]
let make = (~update, ~startText) => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch ((action: action)) {
        | Update(text) => {text: text}
        },
      {text: ""},
    );
  <div>
    <input
      type_="text"
      placeholder=startText
      onChange={e => {
        let text = ReactEvent.Form.target(e)##value;
        dispatch(Update(text));
        update(text);
      }}
    />
  </div>;
};
